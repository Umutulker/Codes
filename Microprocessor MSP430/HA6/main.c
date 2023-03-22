#include <msp430.h>
unsigned int Phase = 0;

#pragma vector=TIMER0_A0_VECTOR  // Timer A0 interrupt service routine (ISR)
__interrupt void TIMER0_A0_ISR(void)
{
       if(Phase > 2){ //if Phase > 2 set it to 0 and set CCR0 to 0 for case 0.
           Phase = 0;
           TA0CCR0 = 0;
       }

       if(Phase == 2){ // if Phase = 2 toggle LED
           P1OUT ^= BIT0;
       }

       if(Phase < 2){  // if Phase < 2 set CCR0 to 0 (because there is no delay needed in Phase 1 and 2)
           TA0CCR0 = 0;
       }

   switch(Phase){

    case 0:
          P1OUT &= ~BIT0; // Led off
    break;

    case 1:
          P1OUT |= BIT0;  // Led on
    break;
    case 2:
      if(P1IN & BIT0){   // if Led is on
          TA0CCR0 = 6553;  // set CCR0 to 6553 for a 50ms delay
      }
      else{
          TA0CCR0 = 58982; // set CCR0 to 58982 for a 450ms delay
      }
     break;

   default:
   break;

  }
}

#pragma vector=PORT1_VECTOR  // Port 1 interrupt service routine (ISR)
__interrupt void Port_1(void)
{
  P1IFG &= ~BIT1;  // P1.1 interrupt flag clear
  TA0CCR0 = 13107; //100ms switchbouncing delay (Entrprellung) Can be changed between 40 ms - 100 ms
  Phase++; // Phase increase

}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |=  BIT0;  // set p1.0 as output
    P1DIR &= ~BIT1;  // set P1.1 as input
    P1OUT &= ~BIT0;  // LED Off
    P1REN |=  BIT1;  // enable resistor (Pull up and down) on p1.1
    P1OUT |=  BIT1;  // pull up active.

    TA0CCTL0 &= ~CCIFG; //clear CCIFG(Flag)
    TA0CCTL0 |= CCIE;  // enable capture-compare interrupt
    TA0CCR0=0; //      // CCR0 is 0 for now
    TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3; // Timer A0 --> Select SMCLK , Up mode , Timer clear , Divide 3

    P1IES |=  BIT1;  // P1.1 interrupt is high to low (button pressed)
    P1IFG &= ~BIT1;  // P1.1 interrupt flag clear
    P1IE  |=  BIT1;  // P1.1 interrupt enable

    __bis_SR_register(GIE); // enable global interrupt

      while(1){

      }
}
