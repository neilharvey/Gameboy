#pragma once
#include "Types.h"

class Mmu
{
	byte Read(word address);

	void Write(word address, byte value);
};

