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
	auto opcode = read_byte();
	execute_opcode(opcode);
}

void Cpu::execute_opcode(const byte& opcode) {
	// clang-format off
	switch (opcode)
	{
		case 0x00: nop();						break;

		case 0x06: ld_r_n(&b, read_byte());		break;
		case 0x0E: ld_r_n(&c, read_byte());		break;
		case 0x16: ld_r_n(&d, read_byte());		break;
		case 0x1E: ld_r_n(&e, read_byte());		break;
		case 0x26: ld_r_n(&h, read_byte());		break;
		case 0x2E: ld_r_n(&l, read_byte());		break;

		case 0x7F: ld_a_n(a);					break;
		case 0x78: ld_a_n(b);					break;
		case 0x79: ld_a_n(c);					break;
		case 0x7A: ld_a_n(d);					break;
		case 0x7B: ld_a_n(e);					break;
		case 0x7C: ld_a_n(h);					break;
		case 0x7D: ld_a_n(l);					break;
		case 0x0A: ld_a_n(mmu.read(bc));		break;
		case 0x1A: ld_a_n(mmu.read(de));		break;
		case 0x7E: ld_a_n(mmu.read(hl));		break;
		//case 0xFA: ld_a_n(read_byte()); break;
		case 0x3E: ld_a_n(read_byte());			break;

		case 0x01: ld_n_nn(&bc, read_word());	break;
		case 0x11: ld_n_nn(&de, read_word());	break;
		case 0x21: ld_n_nn(&hl, read_word());	break;
		case 0x31: ld_n_nn(&sp, read_word());	break;
			
		case 0x01: ld_n_a(bc, a);				break;

		default:
			throw "Opcode not implemented " + opcode;
	}
	// clang-format on
}

void Cpu::nop() {
}

void Cpu::ld_r_n(&byte r, byte n) {
	r = n;
}

void Cpu::ld_n_nn(word& n, word nn) {
	n = nn;
}

void Cpu::ld_a_n(byte n) { 
	a = n; 
}

void Cpu::ld_n_a(byte& n) {
}

byte Cpu::read_byte() {
	return mmu.read(pc++);
}

word Cpu::read_word() {
	byte lo = read_byte();
	byte hi = read_byte();
	word word = ((hi << 8) + lo);
	return word;
}
