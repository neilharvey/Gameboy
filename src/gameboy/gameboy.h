#pragma once

#include <vector>

#include "cartridge.h"
#include "cpu.h"
#include "display.h"
#include "ppu.h"
#include "mmu.h"

class Gameboy {

public:
	Gameboy(Cartridge& cartridge);
	void run();
private:
	Display display;
	Cpu cpu;
	Mmu mmu;
	Ppu ppu;
	std::vector<byte> ram;
};