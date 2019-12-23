#include "Bitwise.h"

bool bitwise::is_bit_set(byte value, int bit) {
    return (value & (1 << bit)) != 0;
}