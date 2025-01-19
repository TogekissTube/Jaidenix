#ifndef _LIMINE_REQUEST_H
#define _LIMINE_REQUEST_H

#include "limine.h"

#define BOOTLOADER  bootloader_info_request
#define TERMINAL    terminal_request
#define MEMMAP      memmap_request
#define KERNEL      kernel_address_request
#define RSDP        rsdp_request
#define SMBIOS      smbios_request

// Declaraciones de las variables globales
extern volatile struct limine_terminal_request terminal_request;
extern volatile struct limine_bootloader_info_request bootloader_info_request;
extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_kernel_address_request kernel_address_request;
extern volatile struct limine_rsdp_request rsdp_request;
extern volatile struct limine_smbios_request smbios_request;

#endif // _LIMINE_REQUEST_H

