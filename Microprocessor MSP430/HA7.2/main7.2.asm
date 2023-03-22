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
main ; Fibonacci rules
      mov #0x2400, R10 ; set R10 to memory adress
      mov #0, 0(R10) ; LSB is 0 (First number of Fibonacci)
      mov #0, 2(R10) ; MSB is 0 (Carry bit)
      mov #1, 4(R10) ; LSB is 1 (Second number of Fibonacci)
      mov #0, 6(R10) ; MSB is 0

fib   mov 2(R10), R13 ; Save MSB of the first number to R13
      mov @R10, R12   ; Save first number of the address of R10 to R12

      add 2(R10), 6(R10); addition MSB of two numbers

      add @R10, 4(R10) ; addition LSB of two numbers
      adc 6(R10)       ; add carry of the summary to MSB

      add #0x0004, R10; increase the address by 4
      mov R13, 6(R10) ; move the value of R13 to MSB of the next number

      mov R12, 4(R10); move the value of R12 (old number, for the addition, 0+1=1,  5+8=13 ...)
      jmp fib        ; jump to loop

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
            
