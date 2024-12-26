#include "kernel/drivers/screen.h"
#include "kernel/panic.h"

// Implementación del kernel panic
void kernel_panic(const char *message) {
    screen_clear();  // Limpia la pantalla para mostrar solo el error
    screen_write("!!! KERNEL PANIC !!!\n");
    screen_write("Reason: ");
    screen_write(message);
    screen_write("\n\nThe system was stopped\n");

    // Bucle infinito para detener el sistema
    while (1) {
        asm volatile("hlt");
    }
}
