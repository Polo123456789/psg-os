.PHONY: all default
default: all
all: psg-os.bin

boot.o: src/kernel/arch/i386/boot.s
	@echo (boot) Creando objeto: boot.o
	@i686-elf-as src/kernel/arch/i386/boot.s -o bin/boot.o

crti.o: src/kernel/arch/i386/crti.s
	@echo (crti) Creando objeto: crti.o
	@i686-elf-as src/kernel/arch/i386/crti.s -o bin/crti.o

crtn.o: src/kernel/arch/i386/crtn.s
	@echo (crtn) Creando objeto: crtn.o
	@i686-elf-as src/kernel/arch/i386/crtn.s -o bin/crtn.o

INCLUDE_FLAGS := -Isrc/lib -Isrc/kernel/include
CC_CXX := i686-elf-g++
CC_CXX_FLAGS := -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

LINKER_SCRIPT := src/kernel/arch/i386/linker.ld
CC_C := i686-elf-gcc
CC_C_FLAGS := -T $(LINKER_SCRIPT) -o bin/psg-os.bin -ffreestanding -O2 -nostdlib -lgcc

LIB_HEADERS := $(wildcard src/lib/*.hpp)
FREE_STANING_LIB_CSTR_SRC := $(wildcard src/lib/freestanding/cstring/*.cpp)
FREE_STANING_LIB_CSTR_OBJ := $(patsubst %.cpp, %.o, $(FREE_STANING_LIB_CSTR_SRC))
FREE_STANING_LIB_OBJ := $(FREE_STANING_LIB_CSTR_OBJ)

$(FREE_STANING_LIB_OBJ): %.o: %.cpp $(LIB_HEADERS)
	@echo (freestanding-lib) Creando objeto: $@
	@$(CC_CXX) -c $< $(CC_CXX_FLAGS) $(INCLUDE_FLAGS) -o $@ 

KERNEL_HEADERS := $(wildcard src/kernel/include/kernel/*.hpp)
KERNEL_ARCH_SRC := $(wildcard src/kernel/arch/i386/*.cpp)
KERNEL_ARCH_OBJ := $(patsubst %.cpp, %.o, $(KERNEL_ARCH_SRC))
KERNEL_SRC := $(wildcard src/kernel/kernel/*.cpp)
KERNEL_OBJ := $(patsubst %.cpp, %.o, $(KERNEL_SRC))

$(KERNEL_ARCH_OBJ): %.o: %.cpp $(KERNEL_HEADERS)
	@echo (kernel-i386) Creando objeto $@
	@$(CC_CXX) -c $< $(CC_CXX_FLAGS) $(INCLUDE_FLAGS) -o $@

$(KERNEL_OBJ): %.o: %.cpp $(KERNEL_HEADERS)
	@echo (kernel) Creando objeto: $@
	@$(CC_CXX) -c $< $(CC_CXX_FLAGS) $(INCLUDE_FLAGS) -o $@

INTERNAL_OBJ := $(FREE_STANING_LIB_OBJ) $(KERNEL_ARCH_OBJ) $(KERNEL_OBJ)

CRTI_OBJ=bin/crti.o
CRTBEGIN_OBJ:=$(shell $(CC_C) $(CC_C_FLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC_C) $(CC_C_FLAGS) -print-file-name=crtend.o)
CRTN_OBJ=bin/crtn.o

LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) bin/boot.o $(INTERNAL_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ)

psg-os.bin: boot.o crti.o crtn.o $(LINK_LIST)
	@echo (Linker) Enlazando todo ...
	@$(CC_C) $(LINK_LIST) $(CC_C_FLAGS)

.PHONY: clean
clean:
	-del $(subst /,\, $(INTERNAL_OBJ))
	-del bin\boot.o
	-del bin\psg-os.bin
