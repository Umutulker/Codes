#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer

    P1DIR |= BIT0; // P1.0 output
    P1OUT &= ~(BIT0); // Led off
    P1DIR &= ~(BIT1); // P1.1 input
    P1REN |= BIT1; // Pull up and down active
    P1OUT |= BIT1; // Pull up on p1.1.

    volatile unsigned int i;
    unsigned int mode = 1;

    while(1)
    {

         if(!(P1IN & BIT1))  // If pressed
         {

             for(i=15000; i>0; i--);

             if(!(P1IN & BIT1))
             {
                 mode++; // mode ++
             }
         }
      goto here;

here_s:   if(!(P1IN & BIT1)) // Special if condition for the last step , 32768hz...
          {

               for(i=600; i>0; i--);

               if(!(P1IN & BIT1))
           {
              mode++;
           }
          }
here:
         switch (mode%6)
         {
         case 0:

         // Reset all, default.
              UCSCTL3 |= SELREF_0;    //XT1 mit FLL
              do
              {
                UCSCTL7 &= ~XT1LFOFFG;                  // Clear XT1 fault flags
              }while (UCSCTL7&XT1LFOFFG);               // Test XT1 fault flag

              UCSCTL4 = SELS_4 + SELM_4 +SELA_0;               // Default MCLK and SMCLK

              P1OUT &= ~(BIT0); // Led off.

         break;

         case 1:
              P1OUT &= ~(BIT0); // Led off.

         break;

         case 2:

              P1OUT |= BIT0; // Led on.

         break;
         case 3:



              P1OUT ^= BIT0; // toggle

              if(P1IN & BIT0) // if Led is on
              {
                  for(i=30000; i>0; i--);
              }
              else            // if Led is off
              {
                  for(i=55924; i>0; i--);
                  for(i=55924; i>0; i--);

              }

         break;

         case 4:
              P2DIR |= BIT2;                            // SMCLK set out to pins
              P2SEL |= BIT2;
              P7DIR |= BIT7;                            // MCLK set out to pins
              P7SEL |= BIT7;

              P5SEL |= BIT2+BIT3;                      // Select XT2
              UCSCTL6 &= ~(XT2OFF);                    // XT2 on
              UCSCTL3 |= SELREF_2;                     // Reference clock = REFOCLK

              UCSCTL4 |= SELA_2;                     // ACLK is even with REFO.

              do
              {
                UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags


                SFRIFG1 &= ~OFIFG;                         // Clear fault flags
              }while (SFRIFG1 & OFIFG);                   // Test oscillator fault flag

              UCSCTL6 &= ~XT2DRIVE0;
              UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2



                P1OUT ^= BIT0;  //Toggle
              if(P1IN & BIT0) //if on
              {
                  for(i=30000; i>0; i--);  //delay

              }
              else
              {
                  for(i=55924; i>0; i--);
                  for(i=55924; i>0; i--);
                  for(i=55924; i>0; i--);

            }
         break;

         case 5:
              P5SEL |= BIT4+BIT5;                       // Port select XT1
              UCSCTL6 &= ~(XT1OFF);                     // XT1 On
              UCSCTL6 |= XCAP_3;
              UCSCTL3 |= SELREF_0 ;                     // Reference clock = XT1

              do
                {
                  UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                                          // Clear XT2,XT1,DCO fault flags
                  SFRIFG1 &= ~OFIFG;                      // Clear fault flags
                }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

              UCSCTL6 &= ~(XT1DRIVE_3);  //decrease f.
              UCSCTL4 = SELA_0;       // ACLK=XT1

              P1OUT ^= BIT0;      // toggle

              if(!(P1IN & BIT0)) //if on
              {
                  for(i=3000; i>0; i--); //delay
              }
              else
              {
                  for(i=3000; i>0; i--);
              }
              goto here_s;
         break;
         default:
         break;
         }
    }
}
