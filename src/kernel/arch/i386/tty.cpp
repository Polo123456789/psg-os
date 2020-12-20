#include <kernel/tty.hpp>

#include "vga.hpp"

namespace tty {

void init() {
    vga::tty_term.init();
}

void put_char(char c) {
    vga::tty_term.put_char(c);
}

void write(const char *data, size_t size) {
    vga::tty_term.write(data, size);
}

void write_string(const char *data) {
    vga::tty_term.write_string(data);
}

} // namespace tty
