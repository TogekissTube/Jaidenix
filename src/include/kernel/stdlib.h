#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

// Convierte un número entero sin signo a una cadena en la base especificada
char *itoa(uint32_t num, char *buffer, int base);

#endif // STDLIB_H
