#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Tienes que utilizar un cross compiler"
#endif

//#if !defined(__i386__)
//#error "Tiene que ser un compilador para 32 bits"
//#endif

// Porque no tenemos la libreria estandar
size_t strlen(const char* str) 
{
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

namespace vga {

// Constantes para los colores en el modo de texto
enum class color : uint8_t {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magenta = 5,
    brown = 6,
    light_grey = 7,
    dark_grey = 8,
    light_blue = 9,
    light_green = 10,
    light_cyan = 11,
    light_red = 12,
    light_magenta = 13,
    light_brown = 14,
    white = 15,
};

static inline color entry_color(color fg, color bg) 
{
    return static_cast<color> (
            static_cast<uint8_t>(fg) | static_cast<uint8_t>(bg) << 4);
}

static inline uint16_t entry(unsigned char uc, color c) 
{
    return static_cast<uint16_t>(uc) | static_cast<uint16_t>(c) << 8;
}

// Tamaño de la terminal
constexpr size_t WIDTH = 80;
constexpr size_t HEIGHT = 25;

} // namespace vga

class terminal {
    public:
        terminal();
        terminal(const terminal&) = delete;
        terminal& operator=(const terminal&) = delete;
        terminal(terminal&&) = delete;
        terminal& operator=(terminal&&) = delete;
        ~terminal() = default;

        void set_color(vga::color color);
        void put_entry_at(char c, vga::color clr, size_t x, size_t y);
        void put_char(char c);
        void write(const char* data, size_t size);
        void write_string(const char* data);
    private:
        size_t row;
        size_t column;
        vga::color color;
        uint16_t* buffer;
};

terminal::terminal() {
    row = 0;
    column = 0;
    color = vga::entry_color(vga::color::light_grey, vga::color::black);
    buffer = reinterpret_cast<uint16_t*>(0xB8000);

    for (size_t y = 0; y < vga::HEIGHT; y++) {
        for (size_t x=0; x < vga::WIDTH; x++) {
            const size_t index = y * vga::WIDTH + x;
            buffer[index] = vga::entry(' ', color);
        }
    }
}

void terminal::set_color(vga::color color) {
    this->color = color;
}

void terminal::put_entry_at(char c, vga::color clr, size_t x, size_t y) {
    const size_t index = y * vga::WIDTH + x;
    buffer[index] = vga::entry(c, clr);
}

void terminal::put_char(char c) {
    put_entry_at(c, color, column, row);
    if (++column == vga::WIDTH) {
        column = 0;
        if (++row == vga::HEIGHT) {
            row = 0;
        }
    }
}

void terminal::write(const char* data, size_t size) {
    for (size_t i = 0; i<size; i++) {
        this->put_char(data[i]);
    }
}

void terminal::write_string(const char* data) {
    this->write(data, strlen(data));
}

extern "C" {

void kernel_main(void) 
{
    terminal t;
    t.write_string("Hola Mundo\n");
}

}
