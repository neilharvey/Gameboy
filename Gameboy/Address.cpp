#include "Address.h"

Address::Address(word value) {
    address = value;
}

Address Address::operator+(byte offset) {
    return Address(address + offset);
}

Address Address::operator-(byte offset) {
    return Address(address - offset);
}
