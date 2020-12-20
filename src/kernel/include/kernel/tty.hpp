#ifndef _PSG_OS_KERNEL_TTY_HPP
#define _PSG_OS_KERNEL_TTY_HPP

#include <stddef.h>

namespace tty {

void init();
void put_char(char c);
void write(const char *data, size_t size);
void write_string(const char *data);

} // namespace tty

#endif
