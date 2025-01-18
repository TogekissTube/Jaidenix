#ifndef _PRINTF_H
#define _PRINTF_H

#include <stddef.h> // Para size_t

void putchar_(char character);
int printf(const char *format, ...);
int snprintf(char *buffer, size_t count, const char *format, ...);

#endif // _PRINTF_H
