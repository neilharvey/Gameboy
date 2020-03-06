#include "Mmu.h"
#include "BootRom.h"

Mmu::Mmu(Ppu ppu, Cartridge cartridge) :

	cartridge(cartridge),
	ppu(ppu),
	vram(0x2000, 0),
	oam(0x0100, 0),
	hram(0x0080, 0),
	wram(0x2000, 0),
	io(0x7F, 0)
{
	booting = true;
}

byte Mmu::read(word address)
{
	if (address <= 0x00FF && booting) {
		return BootRom[address];
	}

	// 0000 - 3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	else if (address >= 0x0000 && address <= 0x3FFF) {
		return cartridge.read(address);
	}

	// 4000 - 7FFF   16KB ROM Bank 01..NN(in cartridge, switchable bank number)
	else if (address >= 0x4000 && address <= 0x7FFF) {
		return cartridge.read(address);
	}

	// 8000 - 9FFF   8KB Video RAM(VRAM) (switchable bank 0 - 1 in CGB Mode)
	else if (address >= 0x8000 && address <= 0x9FFF) {
		return vram[address - 0x8000];
	}

	// A000 - BFFF   8KB External RAM(in cartridge, switchable bank, if any)
	else if (address >= 0xA000 && address <= 0xBFFF) {
		return 0;
	}

	// C000 - CFFF   4KB Work RAM Bank 0 (WRAM)
	else if (address >= 0xC000 && address <= 0xCFFF) {
		return wram[address - 0xC000];
	}

	// D000 - DFFF   4KB Work RAM Bank 1 (WRAM)(switchable bank 1 - 7 in CGB Mode)
	else if (address >= 0xD000 && address <= 0xDFFF) {
		return wram[address - 0xC000];
	}

	// E000 - FDFF   Same as C000 - DDFF(ECHO)    (typically not used)
	else if (address >= 0xE000 && address <= 0xFDFF) {
		return wram[address - 0xE000];
	}

	// FE00 - FE9F   Sprite Attribute Table (OAM)
	else if (address >= 0xFE00 && address <= 0xFE9F) {
		return oam[address - 0xFE00];
	}

	// FEA0 - FEFF   Not Usable
	else if (address >= 0xFEA0 && address <= 0xFEFF) {
		return 0;
	}

	// FF00 - FF7F   I / O Ports
	else if (address >= 0xFF00 && address <= 0xFF7F) {
		return io[address - 0xFF00];
	}

	// FF80 - FFFE   High RAM(HRAM)
	else if (address >= 0xFF80 && address <= 0xFFFE) {
		return hram[address - 0xFF80];
	}

	// FFFF          Interrupt Enable Register


	return 0;
}

void Mmu::write(word address, byte value)
{
	// 0000 - 3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	if (address >= 0x0000 && address <= 0x3FFF) {
		cartridge.write(address, value);
	}

	// 4000 - 7FFF   16KB ROM Bank 01..NN(in cartridge, switchable bank number)
	else if (address >= 0x4000 && address <= 0x7FFF) {
		cartridge.write(address, value);
	}

	// 8000 - 9FFF   8KB Video RAM(VRAM) (switchable bank 0 - 1 in CGB Mode)
	else if (address >= 0x8000 && address <= 0x9FFF) {
		vram[address - 0x8000] = value;
	}

	// A000 - BFFF   8KB External RAM(in cartridge, switchable bank, if any)
	else if (address >= 0xA000 && address <= 0xBFFF) {

	}

	// C000 - CFFF   4KB Work RAM Bank 0 (WRAM)
	else if (address >= 0xC000 && address <= 0xCFFF) {
		wram[address - 0xC000] = value;
	}

	// D000 - DFFF   4KB Work RAM Bank 1 (WRAM)(switchable bank 1 - 7 in CGB Mode)
	else if (address >= 0xC000 && address <= 0xCFFF) {
		wram[address - 0xC000] = value;
	}

	// E000 - FDFF   Same as C000 - DDFF(ECHO)    (typically not used)
	else if (address >= 0xE000 && address <= 0xFDFF) {
		wram[address - 0xE000] = value;
	}

	// FE00 - FE9F   Sprite Attribute Table (OAM)
	else if (address >= 0xFE00 && address <= 0xFE9F) {
		oam[address - 0xFE00] = value;
	}

	// FEA0 - FEFF   Not Usable
	else if (address >= 0xFEA0 && address <= 0xFEFF) {

	}

	// FF00 - FF7F   I / O Ports
	else if (address >= 0xFF00 && address <= 0xFF7F) {
		io[address - 0xFF00] = value;
	}

	// FF80 - FFFE   High RAM(HRAM)
	else if (address >= 0xFF80 && address <= 0xFFFE) {
		hram[address - 0xFF80] = value;
	}
}
