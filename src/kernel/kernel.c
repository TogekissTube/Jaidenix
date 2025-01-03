#include "kernel/drivers/screen.h"
#include "kernel/arch/i386/gdt.h"
#include "kernel/arch/i386/idt.h"
#include "kernel/arch/i386/interrupts.h"

extern void enable_paging();

void main() {
    screen_clear(); // Limpia la pantalla
    init_gdt(); // Habilita la GDT
    init_idt(); // Habilita la IDT
    init_interrupts(); // Inicia el manejador de interrupciones
    asm volatile("sti"); // Habilita las interrupciones
    screen_write("Hello world!\n");
}
