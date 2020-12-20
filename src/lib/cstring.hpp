#ifndef _PSG_OS_LIB_CSTRING
#define _PSG_OS_LIB_CSTRING

#include <stddef.h>

size_t strlen(const char* str);
int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

#endif
