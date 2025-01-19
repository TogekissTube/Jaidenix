#ifndef _BOOTSERVICES_H
#define _BOOTSERVICES_H

#include "limine.h"
#include <stdint.h>

char* get_bootloader_name();
char* get_bootloader_version();

uint64_t get_terminal_count();
uint64_t get_current_terminal();

void set_terminal_writer(uint64_t terminal);
void (*get_terminal_write())(const char*, uint64_t);

uint64_t get_memory_map_entries();
uint64_t get_memory_map_base(uint64_t entry);
uint64_t get_memory_map_length(uint64_t entry);
uint64_t get_memory_map_type(uint64_t entry);

#endif // _BOOTSERVICES_H
