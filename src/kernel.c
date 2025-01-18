#include "bootservices.h"
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

// Función para imprimir una cadena en la terminal
void print(const char* str) {
    void (*writer)(const char*, uint64_t) = get_terminal_write();
    writer(str, strlen(str));  // Pasar la cadena a strlen
}

// Punto de entrada del kernel
void _start() {
    print("Hello world!");
    hlt();
}
