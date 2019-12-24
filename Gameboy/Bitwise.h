#pragma once

#include "Types.h"

namespace bitwise {

    bool is_bit_set(byte value, int bit);
    byte get_lsb(word value);
    byte get_msb(word value);
}