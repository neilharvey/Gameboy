#pragma once

#include <vector>

#include "cartridge.h"
#include "cpu.h"
#include "display.h"
#include "ppu.h"
#include "mmu.h"

class Gameboy {

public:
	Gameboy(Cartridge cartridge, Display display);
	void run();
private:
	Ppu ppu;
	Mmu mmu;
	Cpu cpu;
};