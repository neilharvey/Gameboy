#include "Cpu.h"

Cpu::Cpu(Mmu& m)
{
	mmu = m;

	af = 0;
	bc = 0;
	de = 0;
	hl = 0;
	sp = 0;
	pc = 0;
}

void Cpu::Tick()
{
}
