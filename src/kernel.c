#include "bootservices.h"
#include "util/printf/printf.h"
#include <stdint.h>

#define STRING_MAX_SIZE 65536

// Función para calcular la longitud de una cadena
uint64_t strlen(const char* str) {
    uint64_t len = 0;
    while (str[len] && len < STRING_MAX_SIZE)
        len++;
    return len;
}

// Función para detener el sistema
void hlt() {
    while (1) {
        __asm__("hlt");
    }
}


// Punto de entrada del kernel
void _start() {
    printf("Hello world!");
    hlt();
}
