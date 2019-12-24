#pragma once
#include "Types.h"

class Address {
public:
    Address(word location);

    Address operator+(byte offset);
    Address operator-(byte offset);

private:
    word address = 0x0000;

};