#include "Cpu.h"

Cpu::Cpu(Mmu& m) : 
	mmu(m)
{
	af = 0;
	bc = 0;
	de = 0;
	hl = 0;
	sp = 0;
	pc = 0;
}

void Cpu::tick()
{
	auto opcode = mmu.read(pc++);
	execute_opcode(opcode);
}

void Cpu::execute_opcode(const byte& opcode)
{
	switch (opcode)
	{
	case 0x00: nop(); break;
	default:
		throw "Opcode not implemented " + opcode;
	}
}

void Cpu::nop()
{
}
