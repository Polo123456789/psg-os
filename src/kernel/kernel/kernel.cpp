#if defined(__linux__)
    #error "Tienes que utilizar un cross compiler"
#endif

#if !defined(__i386__)
#error "Tiene que ser un compilador para 32 bits"
#endif

#include <kernel/tty.hpp>
#include <cstring.hpp>

extern "C" {

void kernel_main(void) {
    int e = strlen("Saludos");
    tty::init();
    tty::write_string("Hola mundo.");
}

} // extern "C"
