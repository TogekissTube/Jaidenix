; interrupts.asm
global isr_stub_table

extern isr_handler

section .text
isr_stub_table:
    %macro ISR_ENTRY 1
        push dword %1       ; Empuja el número de interrupción en la pila
        push dword 0        ; Empuja un valor ficticio para alinear la pila (si es necesario)
        call isr_handler    ; Llama al manejador genérico de interrupciones
        add esp, 8          ; Limpia los valores empujados
        iret                ; Retorna de la interrupción
    %endmacro

    ISR_ENTRY 0
    ISR_ENTRY 1
    ISR_ENTRY 2
    ISR_ENTRY 3
    ISR_ENTRY 4
    ISR_ENTRY 5
    ISR_ENTRY 6
    ISR_ENTRY 7
    ISR_ENTRY 8
    ISR_ENTRY 9
    ISR_ENTRY 10
    ISR_ENTRY 11
    ISR_ENTRY 12
    ISR_ENTRY 13
    ISR_ENTRY 14
    ISR_ENTRY 15
    ISR_ENTRY 16
    ISR_ENTRY 17
    ISR_ENTRY 18
    ISR_ENTRY 19
    ISR_ENTRY 20
    ISR_ENTRY 21
    ISR_ENTRY 22
    ISR_ENTRY 23
    ISR_ENTRY 24
    ISR_ENTRY 25
    ISR_ENTRY 26
    ISR_ENTRY 27
    ISR_ENTRY 28
    ISR_ENTRY 29
    ISR_ENTRY 30
    ISR_ENTRY 31

