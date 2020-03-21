#include "Mmu.h"
#include "BootRom.h"

Mmu::Mmu(Ppu& ppu, std::vector<byte>& ram, Cartridge& cartridge) :
	ppu(ppu),
    ram(ram),
	cartridge(cartridge)
{
	booting = true;
}

byte Mmu::read(word address)
{
	if (address <= 0x00FF && booting) {
		return BootRom[address];
	} 

    else if (address <= 0x7fff) {
        return cartridge.read(address);
    }

    else if (address >= 0xff40 && address <= 0xff4b) {
        return ppu.read(address);
    }
    else {
        return ram[address];
    }
}

void Mmu::write(word address, byte value)
{
    if (address >= 0x0100 && address <= 0x7fff) {
        cartridge.write(address, value);
    }
    else if (address >= 0xff40 && address <= 0xff4b) {
         ppu.write(address, value);
    }
    else {
        ram[address] = value;
    }
}