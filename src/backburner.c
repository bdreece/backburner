#include <stddef.h>
#include <stdint.h>

#include "backburner/macro.h"

BACKBURNER_DERIVE(char, char)
BACKBURNER_DERIVE(short, short)
BACKBURNER_DERIVE(int, int)
BACKBURNER_DERIVE(long, long)
BACKBURNER_DERIVE(long long, long_long)
BACKBURNER_DERIVE(bool, bool)
BACKBURNER_DERIVE(uint8_t, u8)
BACKBURNER_DERIVE(uint16_t, u16)
BACKBURNER_DERIVE(uint32_t, u32)
BACKBURNER_DERIVE(uint64_t, u64)
BACKBURNER_DERIVE(int8_t, i8)
BACKBURNER_DERIVE(int16_t, i16)
BACKBURNER_DERIVE(int32_t, i32)
BACKBURNER_DERIVE(size_t, usize)
BACKBURNER_DERIVE(uintptr_t, uintptr)
BACKBURNER_DERIVE(ptrdiff_t, ptrdiff)
BACKBURNER_DERIVE(char *, char_ptr);
BACKBURNER_DERIVE(short *, short_ptr);
BACKBURNER_DERIVE(int *, int_ptr);
BACKBURNER_DERIVE(long *, long_ptr);
BACKBURNER_DERIVE(long long *, long_long_ptr);
BACKBURNER_DERIVE(bool *, bool_ptr);
BACKBURNER_DERIVE(void *, void_ptr);
