;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
main  bis #BIT0,&P1DIR; p1.0
      bic #BIT1,&P1DIR; p1.1 input
      bic #BIT0,&P1OUT; Led off
      bis #BIT1,&P1REN; enable resistor
      bis #BIT1,&P1OUT; Pull up active

      mov #0,R6; Phase
      mov #0,R7; Buttonpressed
mainloop

presstest
      bit #BIT1,&P1IN; check p1.1
      jc  not_pressed; if not pressed go to not_pressed
      cmp #0,R7; compare whether holding or not
      jnz timersetup ; if Buttonpressed is not 0 go directly to timersetup (when holding always go to timersetup without increasing the Phase)

holding_detect ; if Butttonpressed is 0 (enters when the button is for the first time pressed after the previous holding)
      mov #1,R7; set Buttonpressed = 1
      inc R6; increase Phase
      cmp #3,R6; if greater than 2 (equal to 3) reset Phase to 0
      jnz timersetup ; if less or equal 2 go to timersetup

      mov #0,R6; Phase reset
      jmp timersetup

not_pressed ;; if p1.1 not pressed
      mov #0,R7; reset Buttonpressed to 0(
      jmp Phasetest

timersetup
      bic #CCIFG,&TA0CCTL0; clear CCIFG
      bis #CCIE,&TA0CCTL0; enable CC interrupt
      bis #TASSEL_2,&TA0CTL; select source as SMCLK
      bis #MC_1,&TA0CTL; up mode
      bis #TACLR,&TA0CTL; timer clear
      bis #ID_1,&TA0CTL; divide 2
      mov #52428,&TA0CCR0; 100 ms

timer_delay_switchbouncing
      bit #CCIFG,&TA0CCTL0; test CCIFG
      jnc timer_delay_switchbouncing ; if CCIFG is not set yet go back to timer_delay_switchbouncing

Phasetest
      cmp #0,R6 ; compare for Phase 0
      jz  Phase0

      cmp #1,R6 ; compare for Phase 1
      jz  Phase1

      cmp #2,R6 ; compare for Phase 2
      jz  Phase2

Phase0
      bic #BIT0,P1OUT; Led off
      jmp mainloop
Phase1
      bis #BIT0,P1OUT; Led on
      jmp mainloop
Phase2
      xor #BIT0,P1OUT; toggle Led

      bit #BIT0,P1IN; test whether Led is on or off
      jnc off

on
      bic #CCIFG,&TA1CCTL0; clear CCIFG
      bis #CCIE,&TA1CCTL0; enable CC interrupt
      bis #TASSEL_2,&TA1CTL; select source as SMCLK
      bis #MC_1,&TA1CTL; up mode
      bis #TACLR,&TA1CTL; timer clear
      bis #ID_3,&TA1CTL; divide 8
      mov #6553,&TA1CCR0; CCR0 = 6553 for 50ms delay
timer_A1_delay_on
      bit #CCIFG,&TA1CCTL0; test CCIFG
      jnc timer_A1_delay_on; if CCIFG not set yet go to timer_A1_delay_on
      jmp mainloop

off
      bic #CCIFG,&TA1CCTL0; clear CCIFG
      bis #CCIE,&TA1CCTL0; enable CC interrupt
      bis #TASSEL_2,&TA1CTL; select source as SMCLK
      bis #MC_1,&TA1CTL; up mode
      bis #TACLR,&TA1CTL; timer clear
      bis #ID_3,&TA1CTL; divide 8
      mov #58982,&TA1CCR0;  CCR0 = 58982 for 450ms delay

timer_A1_delay_off
      bit #CCIFG,&TA1CCTL0; test CCIFG
      jnc timer_A1_delay_off; if CCIFG not set yet go to timer_A1_delay_off
      jmp mainloop
      nop
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
