# Definición de variables
CC = gcc
ASM = nasm
CFLAGS = -Wall -m32 -ffreestanding -fno-builtin -nostdlib -O2
LDFLAGS = -m32 -ffreestanding -T linker.ld
SRC_DIRS = src src/kernel src/kernel/drivers src/kernel/arch/i386
OBJ_DIR = obj
BUILD_DIR = build
ISO_DIR = iso/boot
EXEC = $(BUILD_DIR)/kernel.elf
ISO = jaidenix.iso

# Archivos fuente
C_SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
ASM_SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.asm))

# Archivos objeto resultantes
C_OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst %.asm, $(OBJ_DIR)/%.o, $(ASM_SOURCES))

# Todos los objetos (C + ASM)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Regla predeterminada
all: $(BUILD_DIR) $(ISO)

# Regla para crear el directorio build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para crear el directorio iso/boot
$(ISO_DIR):
	mkdir -p $(ISO_DIR)

# Regla para crear el directorio obj y sus subdirectorios
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@$(foreach dir, $(SRC_DIRS), mkdir -p $(OBJ_DIR)/$(dir);)

# Regla para compilar archivos .c en .o
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I src/include -c $< -o $@

# Regla para compilar archivos .asm en .o
$(OBJ_DIR)/%.o: %.asm | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(ASM) -f elf32 $< -o $@

# Regla para crear el ejecutable final
$(EXEC): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Regla para crear la imagen ISO
$(ISO): $(EXEC) | $(ISO_DIR)
	cp $(EXEC) $(ISO_DIR)
	grub2-mkrescue -o $@ iso/

# Limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) $(ISO)
