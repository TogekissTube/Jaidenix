#include "kernel/arch/i386/interrupts.h"
#include "kernel/arch/i386/idt.h"
#include "kernel/drivers/screen.h"
#include "kernel/panic.h" // Incluir soporte para kernel_panic

extern void isr_stub_table();  // Stub de interrupciones (ensamblador)

// Nombres descriptivos para las excepciones de CPU
const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// Manejador genérico de interrupciones
void isr_handler(uint32_t interrupt_number) {
    screen_write("Interrupción recibida: ");
    screen_write(interrupt_number); // Supongamos que esta función escribe números en pantalla
    screen_write("\n");

    // Verifica si es una excepción de CPU crítica
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
        idt_set_entry(i, (uint32_t)isr_stub_table + i * 8, 0x08, 0x8E);
    }
}

