#include "kernel_printer.h"
#include "../bootservices.h"

#include <stdint.h>

void _putchar(char character) {

    void (*writer)(const char*, uint64_t) = get_terminal_write();
    writer(&character, 1); 
}