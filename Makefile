.PHONY: all default
default: all
all: psg-os.bin

boot.o: src/kernel/arch/i386/boot.s
	@echo (boot) Creando objeto: boot.o
	@i686-elf-as src/kernel/arch/i386/boot.s -o bin/boot.o

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

psg-os.bin: boot.o $(FREE_STANING_LIB_OBJ) $(KERNEL_ARCH_OBJ) $(KERNEL_OBJ)
	@echo (Linker) Enlazando todo ...
	@$(CC_CXX) bin/boot.o $(FREE_STANING_LIB_OBJ) $(KERNEL_ARCH_OBJ) \
	    $(KERNEL_OBJ) $(CC_C_FLAGS)

.PHONY: clean
clean:
	-del $(subst /,\, $(FREE_STANING_LIB_CSTR_OBJ))
	-del $(subst /,\, $(KERNEL_ARCH_OBJ))
	-del $(subst /,\, $(KERNEL_OBJ))
	-del bin\boot.o
	-del bin\psg-os.bin
