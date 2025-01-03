cd src
nasm -f elf32 boot.asm -o boot.o
cd kernel
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/
gcc -m32 -c panic.c -o panic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/
gcc -m32 -c stdlib.c -o stdlib.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/
gcc -m32 -c drivers/screen.c -o screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../include/
cd arch
cd i386
nasm -f elf32 gdt.asm -o gdta.o
nasm -f elf32 idt.asm -o idta.o
nasm -f elf32 interrupts.asm -o interruptsa.o
gcc -m32 -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../../../include/
gcc -m32 -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../../../include/
gcc -m32 -c interrupts.c -o interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ../../../include/
cd ..
cd ..
cd ..
cd ..
ld -m elf_i386 -T linker.ld -o kernel.elf src/boot.o src/kernel/kernel.o src/kernel/screen.o src/kernel/arch/i386/gdta.o src/kernel/arch/i386/gdt.o src/kernel/arch/i386/idta.o src/kernel/arch/i386/idt.o src/kernel/panic.o src/kernel/arch/i386/interruptsa.o src/kernel/arch/i386/interrupts.o src/kernel/stdlib.o 
mv kernel.elf iso/boot/
grub-mkrescue -o jaidenix.iso iso/

# In Red Hat based Linux systems grub-mkrescue is grub2-mkrescue. 

grub2-mkrescue -o jaidenix.iso iso/
