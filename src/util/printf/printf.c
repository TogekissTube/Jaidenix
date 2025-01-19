#include "printf.h"
#include "../../boot/bootservices.h"
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

// Función auxiliar para imprimir números en cualquier base
static void print_number_base(uint64_t num, int base, int uppercase) {
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char buffer[64];
    int i = 0;

    // Si el número es 0, imprimimos "0" directamente
    if (num == 0) {
        putchar_('0');
        return;
    }

    // Convertimos el número a la base especificada
    while (num > 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    // Imprimimos en orden inverso
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
                if (num < 0) {
                    putchar_('-');
                    num = -num;
                }
                print_number_base((uint64_t)num, 10, 0);
            } else if (*format == 'x') {
                uint32_t num = va_arg(args, uint32_t);
                print_number_base(num, 16, 0);
            } else if (*format == 'X') {
                uint32_t num = va_arg(args, uint32_t);
                print_number_base(num, 16, 1);
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
                char temp[20];
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
            } else if (*format == 'x' || *format == 'X') {
                uint32_t num = va_arg(args, uint32_t);
                char temp[20];
                int temp_len = 0;
                const char *digits = (*format == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";

                do {
                    temp[temp_len++] = digits[num % 16];
                    num /= 16;
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

    *buf_ptr = '\0';
    va_end(args);
    return written;  // Devuelve el número de caracteres escritos (sin incluir el terminador).
}
