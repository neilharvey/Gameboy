#include "Cpu.h"

Cpu::Cpu(Mmu& m) : mmu(m) {
	af = 0;
	bc = 0;
	de = 0;
	hl = 0;
	sp = 0;
	pc = 0;
}

void Cpu::tick() {
	auto opcode = next_byte();
	execute_opcode(opcode);
}

void Cpu::execute_opcode(const byte& opcode) {
	// clang-format off
	switch (opcode)
	{
		case 0x00: nop();						break;

		default:
			throw "Opcode not implemented " + opcode;
	}
	// clang-format on
}

byte Cpu::next_byte() {
	return mmu.read(pc++);
}

word Cpu::next_word() {
	byte lo = next_byte();
	byte hi = next_byte();
	word word = ((hi << 8) + lo);
	return word;
}