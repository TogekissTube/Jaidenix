#include "kernel/drivers/screen.h"
#include "kernel/arch/i386/gdt.h"
#include "kernel/arch/i386/idt.h"
#include "kernel/arch/i386/interrupts.h"

void main() {
    screen_clear(); // Limpia la pantalla
    init_gdt();
    init_idt();
    init_interrupts();
	asm volatile("sti");

	int a = 1;
    int b = 0;
    int c = a / b;

    screen_write("Hello world!\n");
}
