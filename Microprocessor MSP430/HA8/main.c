#include <msp430.h> 
int Phase=0;
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    TA0CCR0 = 0;
    if(Phase > 5){
        Phase = 0;
    }

    if(Phase < 0){
        Phase = 0;
    }
    switch(Phase){
    case 0:   P4OUT &= ~BIT7;
    break;

    case 1:   P4OUT |= BIT7;
              TB0CCTL1 = OUTMOD_6;
              TB0CCR1 = 40;
    break;

    case 2:   TB0CCTL2 = OUTMOD_6;
              TB0CCR2 = 80;
    break;

    case 3:   TB0CCTL3 = OUTMOD_6;
              TB0CCR3 = 120 ;

    break;

    case 4:   TB0CCTL4 = OUTMOD_6;
              TB0CCR4 = 160;
    break;

    case 5:   TB0CCTL5 = OUTMOD_6;
              TB0CCR5 = 200;
    break;

    }

}

#pragma vector=PORT2_VECTOR
__interrupt void Port2(void)
{
    P2IFG &= ~BIT1;  // P2.1 interrupt flag clear
    TA0CCR0 = 13107;

    Phase++;
}


#pragma vector=PORT1_VECTOR
__interrupt void Port1(void)
{
    P1IFG &= ~BIT1;  // P1.1 interrupt flag clear
    TA0CCR0 = 13107;

    Phase--;
}

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    PMAPKEYID = 0X2D52;
	P4MAP7 = PM_TB0CCR1A;
	PMAPKEYID = 0X0000;

    P4DIR |= BIT7;
    P4SEL |= BIT7;
    P4OUT &= ~BIT7;

	P2DIR &= ~BIT1;
    P2REN |= BIT1;
	P2OUT |= BIT1;

	P1DIR &= ~BIT1;
	P1REN |= BIT1;
	P1OUT |= BIT1;

	P1IES |=  BIT1;  // P1.1 interrupt is high to low (button pressed)
    P1IFG &= ~BIT1;  // P1.1 interrupt flag clear
    P1IE  |=  BIT1;  // P1.1 interrupt enable

    P2IES |=  BIT1;  // P2.1 interrupt is high to low (button pressed)
    P2IFG &= ~BIT1;  // P2.1 interrupt flag clear
    P2IE  |=  BIT1;  // P2.1 interrupt enable

    TA0CCTL0 &= ~CCIFG; //clear CCIFG(Flag)
    TA0CCTL0 |= CCIE;  // enable capture-compare interrupt
    TA0CCR0=0; //      // CCR0 is 0 for now
    TA0CTL = TASSEL_2 + MC_1 + TACLR + ID_3;

    TB0CCR0 = 200-1;
    TB0CTL = TBSSEL_1 + MC_3;

    __bis_SR_register(GIE);
	while(1)
	{

	}
}
