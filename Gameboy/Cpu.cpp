#include "Cpu.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

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
		case 0x00: return nop();

		case 0x01: return ld(bc, next_word());
		case 0x11: return ld(de, next_word());
		case 0x21: return ld(hl, next_word());
		case 0x31: return ld(sp, next_word());

		default:
			not_implemented(opcode);
	}
	// clang-format on
}

void Cpu::ld(word& r, word nn)
{
	r = nn;
}

void Cpu::nop() {}

byte Cpu::next_byte() {
	return mmu.read(pc++);
}

word Cpu::next_word() {
	byte lo = next_byte();
	byte hi = next_byte();
	word word = ((hi << 8) + lo);
	return word;
}

void Cpu::not_implemented(byte opcode)
{
	std::stringstream ss;
	ss << "unknown opcode 0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)opcode;
	throw std::out_of_range(ss.str());
}