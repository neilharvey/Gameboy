#pragma once
#include "Types.h"

namespace bitwise {

    bool is_bit_set(byte value, byte bit)
    {
        return value & (1 << bit) != 0;
    }

    byte set_bit(byte value, byte bit)
    {
        auto value_set = value | (1 << bit);
        return static_cast<u8>(value_set);
    }
}