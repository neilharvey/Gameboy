#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "Cpu.h"
#include "Bitwise.h"

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

    case 0x06: return ld(b, next_byte());
    case 0x0E: return ld(c, next_byte());
    case 0x16: return ld(d, next_byte());
    case 0x1E: return ld(e, next_byte());
    case 0x26: return ld(h, next_byte());
    case 0x2E: return ld(l, next_byte());

    case 0x7F: return ld(a, a);
    case 0x78: return ld(a, b);
    case 0x79: return ld(a, c);
    case 0x7A: return ld(a, d);
    case 0x7B: return ld(a, e);
    case 0x7C: return ld(a, h);
    case 0x7D: return ld(a, l);
    case 0x7E: return ld(a, mmu.read(hl));
    case 0x40: return ld(b, b);
    case 0x41: return ld(b, c);
    case 0x42: return ld(b, d);
    case 0x43: return ld(b, e);
    case 0x44: return ld(b, h);
    case 0x45: return ld(b, l);
    case 0x46: return ld(b, mmu.read(hl));
    case 0x47: return ld(b, a);
    case 0x48: return ld(c, b);
    case 0x49: return ld(c, c);
    case 0x4A: return ld(c, d);
    case 0x4B: return ld(c, e);
    case 0x4C: return ld(c, h);
    case 0x4D: return ld(c, l);
    case 0x4E: return ld(c, mmu.read(hl));
    case 0x4F: return ld(c, a);
    case 0x50: return ld(d, b);
    case 0x51: return ld(d, c);
    case 0x52: return ld(d, d);
    case 0x53: return ld(d, e);
    case 0x54: return ld(d, h);
    case 0x55: return ld(d, l);
    case 0x56: return ld(d, mmu.read(hl));
    case 0x57: return ld(d, a);
    case 0x58: return ld(e, b);
    case 0x59: return ld(e, c);
    case 0x5A: return ld(e, d);
    case 0x5B: return ld(e, e);
    case 0x5C: return ld(e, h);
    case 0x5D: return ld(e, l);
    case 0x5E: return ld(e, mmu.read(hl));
    case 0x60: return ld(h, b);
    case 0x5F: return ld(e, a);
    case 0x67: return ld(h, a);
    case 0x6F: return ld(l, a);

	case 0x01: return ld(bc, next_word());
	case 0x11: return ld(de, next_word());
    case 0x20: return jr(Condition::NZ, next_signed_byte());
	case 0x21: return ld(hl, next_word());
	case 0x31: return ld(sp, next_word());

    case 0x32: return ldd_hl_a();

	case 0xAF: return xorn(a);
	case 0xA8: return xorn(b);
	case 0xA9: return xorn(c);
	case 0xAA: return xorn(d);
	case 0xAB: return xorn(e);
	case 0xAC: return xorn(h);
	case 0xAD: return xorn(l);
	case 0xAE: return xorn(mmu.read(hl));
	case 0xEE: return xorn(next_byte());

    case 0xCB: return cb(next_byte());


    //case 0x02: return ld(bc,a);
    //case 0x12: return ld(de,a);
    //case 0x77: return ld(hl,a);
    //case 0xEA: return ld(next_word(), a);


    

	default:
		not_implemented(opcode);
	}
    // clang-format on
}

void Cpu::ld(byte& r, byte n) {
    r = n;
}

void Cpu::ld_a_c(byte c) {
}

void Cpu::ld_c_a(byte c) {
}

void Cpu::ldd_a_hl() {
}

void Cpu::ldd_hl_a() {
    mmu.write(hl, a);
    hl--;
}

void Cpu::ldi_a_hl() {
}

void Cpu::ldi_hl_a() {
}

void Cpu::ldh_n_a(byte n) {
}

void Cpu::ldh_a_b(byte n) {
}

void Cpu::ld(word& r, word nn) {
    r = nn;
}

void Cpu::ld_sp_hl() {
}

void Cpu::ldhl_sp(byte n) {
}

void Cpu::ld_sp(word nn) {
}

void Cpu::xorn(byte n) {
    byte result = a ^ n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, false);

    a = result;
}

void Cpu::nop() {}

void Cpu::cb(byte opcode) {
    // clang-format off
	switch (opcode)
	{
        case 0x7C: return bit(7, h);
    	default:
	    	not_implemented(opcode);
	}
    // clang-format on
}

void Cpu::bit(int b, byte r) {

    bool result = bitwise::is_bit_set(r, b);

    set_flag(Flag::Z, !result);
    set_flag(Flag::N, false);
    set_flag(Flag::H, true);
}

void Cpu::jr(sbyte n) {
    pc = pc + n;
}

void Cpu::jr(Condition cc, sbyte n) {
    if (test_condition(cc)) {
        jr(n);
    }
}

byte Cpu::next_byte() {
    return mmu.read(pc++);
}

sbyte Cpu::next_signed_byte() {
    return sbyte(next_byte());
}

word Cpu::next_word() {
    byte lo = next_byte();
    byte hi = next_byte();
    word word = ((hi << 8) + lo);
    return word;
}

bool Cpu::get_flag(Flag flag) {
    return bitwise::is_bit_set(f, (int)flag);
}

void Cpu::set_flag(Flag flag, bool value) {
    byte index = (byte)flag;
    byte mask = 1 << index;
    f = value ? (f | mask) : (f & ~mask);
}

bool Cpu::test_condition(Condition cc) {

    switch (cc) {
    case Condition::Z:
        return get_flag(Flag::Z);
    case Condition::NZ:
        return !get_flag(Flag::Z);
    case Condition::C:
        return get_flag(Flag::C);
    case Condition::NC:
        return !get_flag(Flag::C);
    }
}

void Cpu::not_implemented(byte opcode) {
    std::stringstream ss;
    ss << "unknown opcode 0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)opcode;
    throw std::out_of_range(ss.str());
}