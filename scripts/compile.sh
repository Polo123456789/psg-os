i686-elf-as src/boot.s -o bin/boot.o
i686-elf-g++ -c src/kernel.cpp -o bin/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -T src/linker.ld -o bin/myos.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc