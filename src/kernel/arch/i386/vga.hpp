#include <stdint.h>

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


static inline color entry_color(color fg, color bg) {
    return static_cast<color>(static_cast<uint8_t>(fg)
                              | static_cast<uint8_t>(bg) << 4);
}

static inline uint16_t entry(unsigned char uc, color c) {
    return static_cast<uint16_t>(uc) | static_cast<uint16_t>(c) << 8;
}

// Tamaño de la Terminal
constexpr size_t WIDTH = 80;
constexpr size_t HEIGHT = 25;

class Terminal {
   public:
    Terminal() = default;
    Terminal(const Terminal &) = delete;
    Terminal &operator=(const Terminal &) = delete;
    Terminal(Terminal &&) = delete;
    Terminal &operator=(Terminal &&) = delete;
    ~Terminal() = default;

    void init();
    void set_color(vga::color color);
    void put_entry_at(char c, vga::color clr, size_t x, size_t y);
    void put_char(char c);
    void write(const char *data, size_t size);
    void write_string(const char *data);

   private:
    size_t     row = 0;
    size_t     column = 0;
    vga::color color = vga::entry_color(vga::color::light_grey, vga::color::black);
    uint16_t * buffer = reinterpret_cast<uint16_t *>(0xB8000);//NOLINT
};

extern Terminal tty_term;

} // namespace vga

