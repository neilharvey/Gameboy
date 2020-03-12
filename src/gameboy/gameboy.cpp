#include "gameboy.h"

Gameboy::Gameboy(Cartridge cartridge, Display display) :
	ppu(display),
	mmu(ppu, cartridge),
	cpu(mmu)
{
}

void Gameboy::run()
{
	while (cpu.pc != 0x100) {
		cpu.tick();
		ppu.tick();
	}
}
