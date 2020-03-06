#include "gameboy.h"

Gameboy::Gameboy(Cartridge cartridge, Display display) :
	cartridge(cartridge),
	gpu(display), 
	mmu(gpu, cartridge), 
	cpu(mmu)
{

}