#include <cstring.hpp>

#include "vga.hpp"

namespace vga {

void Terminal::init() {
    for (size_t y = 0; y < vga::HEIGHT; y++) {
        for (size_t x = 0; x < vga::WIDTH; x++) {
            const size_t index = y * vga::WIDTH + x;
            buffer[index] = vga::entry(' ', color);
        }
    }
}

void Terminal::set_color(vga::color color) {
    this->color = color;
}

void Terminal::put_entry_at(char c, vga::color clr, size_t x, size_t y) {
    const size_t index = y * vga::WIDTH + x;
    buffer[index] = vga::entry(c, clr);
}

void Terminal::put_char(char c) {
    put_entry_at(c, color, column, row);
    if (++column == vga::WIDTH) {
        column = 0;
        if (++row == vga::HEIGHT) {
            row = 0;
        }
    }
}

void Terminal::write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        this->put_char(data[i]);
    }
}

void Terminal::write_string(const char *data) {
    this->write(data, strlen(data));
}

Terminal tty_term;

} // namespace vga
