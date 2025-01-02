#include "kernel/arch/i386/interrupts.h"
#include "kernel/arch/i386/idt.h"
#include "kernel/drivers/screen.h"
#include "kernel/panic.h"
#include "kernel/stdlib.h"
#include <stdint.h>

// Declaración de la tabla de stubs
extern void (*isr_stub_table[])();  // Tabla de punteros a manejadores de interrupción

// Mensajes descriptivos para las excepciones de CPU
const char *exception_messages[] = {
    "Division By Zero", "Debug", "Non Maskable Interrupt", "Breakpoint",
    "Into Detected Overflow", "Out of Bounds", "Invalid Opcode",
    "No Coprocessor", "Double Fault", "Coprocessor Segment Overrun",
    "Bad TSS", "Segment Not Present", "Stack Fault",
    "General Protection Fault", "Page Fault", "Unknown Interrupt",
    "Coprocessor Fault", "Alignment Check", "Machine Check",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

// Manejador genérico de interrupciones
void isr_handler(uint32_t interrupt_number) {
    char buffer[33];
    char *number_str = itoa(interrupt_number, buffer, 10);

    screen_write("Interrupción recibida: ");
    screen_write(number_str);
    screen_write("\n");

    if (interrupt_number < 32) {
        const char *message = exception_messages[interrupt_number];
        kernel_panic(message);
    } else {
        screen_write("Interrupción no crítica manejada correctamente.\n");
    }
}

// Inicialización de interrupciones
void init_interrupts() {
    for (int i = 0; i < 32; i++) {
        idt_set_entry(i, (uint32_t)isr_stub_table[i], 0x08, 0x8E);
    }
}

