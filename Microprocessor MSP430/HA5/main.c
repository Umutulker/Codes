#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  P1REN |= BIT1;   // Pull up and down active on P1.1
  P1OUT |= BIT1;   // Pull up
  volatile unsigned int Buttonpressed = 0; // for the press control
  unsigned int Phase = 0;

  while(1)
      {

           if(!(P1IN & BIT1))
           {
             if(Buttonpressed == 0){  // if pressed
                 Buttonpressed = 1;
                 Phase ++;

               if(Phase > 2){  // if Phase > 2 set it to 0.
                   Phase = 0;
               }
             }
               TA0CCTL0 &= ~(CCIFG); //  delay , clear CCIFG(Flag)
               TA0CCTL0 |= CCIE; //Capture Compare interrupt enable
               TA0CCR0=52428; // 100 ms delay
               TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_1; // Timer A0 --> Select SMCLK , Up mode , Timer clear , Divide 2

             while(1){

                if(TA0CCTL0 & CCIFG){ // if interrupt flag is set
                   break;
                }
              }

           }
           else { // if not pressed, when not holding the button
               Buttonpressed = 0;
           }

           switch (Phase)
           {
           case 0:
                P1OUT &= ~(BIT0); // Led off

           break;
           case 1:
                P1OUT |= BIT0; // Led on

           break;
           case 2:
                P1OUT ^= BIT0; // toggle Led

                 TA1CCTL0 &= ~CCIFG; //clear CCIFG(Flag)
                 TA1CCR0=58982; // 450 ms delay
                 TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3; // Timer A1 --> Select SMCLK , Up mode , Timer clear , Divide 8

                  while(1){
                      if(TA1CCTL0 & CCIFG){ // if interrupt flag is set
                        break;
                    }
                   }
                P1OUT ^= BIT0; // toggle Led

                 TA1CCTL0 &= ~(CCIFG); //clear CCIFG(Flag)
                 TA1CCR0 = 6553; // 50 ms delay
                 TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_3; // Timer A1 --> Select SMCLK , Up mode , Timer clear , Divide 8

                  while(1){
                       if(TA1CCTL0 & CCIFG){
                        break;
                       }
                  }

           break;
           default:
           break;
           }
      }
}
