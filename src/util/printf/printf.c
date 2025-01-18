
#include "printf.h"
#include "../../bootservices.h"
#include <stdint.h>
#include <stdarg.h> // Necesario para va_list, va_start, va_end

void putchar_(char character) {
    void (*writer)(const char *, uint64_t) = get_terminal_write();
    writer(&character, 1);
}

// Función auxiliar para imprimir cadenas
static void puts(const char *str) {
    while (*str) {
        if (*str == '\n') {
            putchar_('\n'); // Manejar nueva línea
            putchar_('\r'); // Retorno de carro para alineación
        } else {
            putchar_(*str);
        }
        str++;
    }
}

// Función auxiliar para imprimir números enteros
static void print_number(int num) {
    if (num < 0) {
        putchar_('-');
        num = -num;
    }

    char buffer[10];
    int i = 0;

    do {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    } while (num > 0);

    while (i--) {
        putchar_(buffer[i]);
    }
}

// Implementación de printf
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            format++;
            if (*format == 's') {
                const char *str = va_arg(args, const char *);
                puts(str);
            } else if (*format == 'd') {
                int num = va_arg(args, int);
                print_number(num);
            } else {
                putchar_('%');
                putchar_(*format);
            }
        } else if (*format == '\n') {
            putchar_('\n'); // Salto de línea
            putchar_('\r'); // Retorno de carro para alineación
        } else {
            putchar_(*format);
        }
        format++;
    }

    va_end(args);
    return 0;
}

// Implementación de snprintf (simple, para usar buffers)
int snprintf(char *buffer, size_t count, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Crear un puntero para escribir en el buffer
    char *buf_ptr = buffer;
    size_t written = 0;

    while (*format && written < count - 1) {
        if (*format == '%' && *(format + 1)) {
            format++;
            if (*format == 's') {
                const char *str = va_arg(args, const char *);
                while (*str && written < count - 1) {
                    *buf_ptr++ = *str++;
                    written++;
                }
            } else if (*format == 'd') {
                int num = va_arg(args, int);
                char temp[10];
                int temp_len = 0;

                if (num < 0) {
                    if (written < count - 1) {
                        *buf_ptr++ = '-';
                        written++;
                    }
                    num = -num;
                }

                do {
                    temp[temp_len++] = '0' + (num % 10);
                    num /= 10;
                } while (num > 0);

                while (temp_len-- > 0 && written < count - 1) {
                    *buf_ptr++ = temp[temp_len];
                    written++;
                }
            } else {
                if (written < count - 1) {
                    *buf_ptr++ = '%';
                    written++;
                }
                if (written < count - 1) {
                    *buf_ptr++ = *format;
                    written++;
                }
            }
        } else {
            *buf_ptr++ = *format;
            written++;
        }
        format++;
    }

    *buf_ptr = '\0'; // Terminar la cadena
    va_end(args);
    return written;  // Devuelve el número de caracteres escritos (sin incluir el terminador).
}
