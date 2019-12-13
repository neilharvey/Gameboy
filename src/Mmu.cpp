#include "Mmu.h"
#include "BootRom.h"

byte Mmu::read(word address)
{
	if (address <= 0x00FF) {
		return BootRom[address];
	}
	else {
		return ram[address];
	}

}

void Mmu::write(word address, byte value)
{
	if (address <= 0x00FF) {
		// warn
	}
	else {
		ram[address] = value;
	}
}