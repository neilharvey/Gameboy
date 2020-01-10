#include "Bitwise.h"

bool bitwise::is_bit_set(byte value, int bit) {
    return (value & (1 << bit)) != 0;
}

byte bitwise::set_bit(byte value, int bit) {
    return value | 1 << bit;
}

byte bitwise::clear_bit(byte value, int bit) {
    return value & ~(1 << bit);
}

byte bitwise::get_lsb(word value) {
    return value & 0xFF;
}

byte bitwise::get_msb(word value) {
    return ((value >> 8) & 0xFF);
}