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
_main       bis.b #00000001b,&P1DIR; set direction. P1.0 output
            bis.b #00000010b,&P1REN; enable resistor p1.1
            bis.b #00000010b,&P1OUT; enable pull up on p1.1
            mov   #2,R5;constant, check
            mov   #4,R6;constant
            mov   #1,R4; counter
mainloop    bic.b #00000001b,&P1OUT; clear P1.0  LED off

loop        cmp   R4,R6; compare
            jeq   here ; if zero bit is set go to here
            jmp   presstest; jump to presstest

here        mov   #1,R4; reset R4
            jmp   mainloop ; jump to mainloop

presstest   bit.b #00000010b,&P1IN; test bit p1.1
            jnc   ent; if pressed (carry=0) go to entprellung
            cmp   R4,R5; compare
            jeq   press1; if zero bit is set go to press1
            jn    press2; if negative bit is set go to press2
            jmp   loop; jump to loop

ent         mov.w #34952 ,R9; delay 100ms R9= delay seconds / ( cycle*(1/Hz) )  R9= 0.1 / (3* (1 / 1048576) ) = 34952.53333333...
count       dec   R9; 1 cycle
            jnz   count; 2 cycle
            inc   R4; increase count
            cmp   R4,R5; compare
            jeq   press1; if zero bit is set go to press1
            jn    press2; if negative bit is set go to jn

press1      bis.b #00000001b,&P1OUT; set p1.0, LED on
            jmp   loop; jump to loop

press2      bic.b #00000001b,&P1OUT; toggle LED off  lights up 2 times a second. 450ms off 50ms on...

OFF         mov.w #52428 ,R12; 450ms delay off R12 = 157286.4 passed 16 bit. so divide into 3. 52428.8
off1        dec   R12; 1 cycle decrease by 1
            jnz   off1; 2 cycle if Zeroflag not set go to off
            mov.w #52428 ,R12
off2        dec   R12; 1 cycle
            jnz   off2;2 cycle
            mov.w #52428 ,R12
off3        dec   R12; 1 cycle
            jnz   off3;2 cycle

            bis.b #00000001b,&P1OUT; toggle last situation LED on
ON          mov.w #17476 ,R11; 50ms R11=17476.266666...
on1         dec   R11; 1 cycle  decrease by 1
            jnz   on1;  2 cycle  if Zeroflag not set go to on1

            jmp   loop; jump to loop
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
            
