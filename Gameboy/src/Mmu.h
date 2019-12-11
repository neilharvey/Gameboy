#pragma once
#include "Types.h"
#include "Bootrom.h"

class Mmu
{
public:
	byte read(word address);

	void write(word address, byte value);
private:
	byte ram[0xFFFF];
};

