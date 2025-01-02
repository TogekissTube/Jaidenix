#include "stdlib.h"
#include <stdint.h>

char *itoa(uint32_t num, char *buffer, int base) {
    static const char digits[] = "0123456789ABCDEF";
    char *ptr = buffer + 32; // Apunta al final del buffer (reserva espacio para '\0')
    *--ptr = '\0'; // Agrega el terminador nulo

    if (num == 0) {
        *--ptr = '0'; // Si el número es 0, simplemente escribe '0'
        return ptr;
    }

    while (num > 0) {
        *--ptr = digits[num % base]; // Convierte el dígito más a la derecha
        num /= base; // Reduce el número
    }

    return ptr; // Devuelve un puntero a la cadena resultante
}

