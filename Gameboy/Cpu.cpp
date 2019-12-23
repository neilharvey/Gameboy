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
	case 0x01: return ld(bc, next_word());
    //case 0x02: return ld(mmu.read(bc), a);
    case 0x0A: return ld(a, mmu.read(bc));
    case 0x06: return ld(b, next_byte());
    case 0x0E: return ld(c, next_byte());
	case 0x11: return ld(de, next_word());
    //case 0x12: return ld(mmu.read(de),a);
    case 0x16: return ld(d, next_byte());
    case 0x1A: return ld(a, mmu.read(de));
    case 0x20: return jr(Condition::NZ, next_signed_byte());
	case 0x21: return ld(hl, next_word());
    case 0x22: return ldi_hl_a();
    case 0x2A: return ldi_a_hl();
    case 0x1E: return ld(e, next_byte());
    case 0x26: return ld(h, next_byte());
    case 0x2E: return ld(l, next_byte());
	case 0x31: return ld(sp, next_word());
    case 0x32: return ldd_hl_a();
    //case 0x36: return ld(mmu.read(hl), next_byte());
    case 0x3A: return ldd_a_hl();
    case 0x3E: return ld(a, next_byte());
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
    case 0x5F: return ld(e, a);
    case 0x60: return ld(h, b);
    case 0x61: return ld(h, c);
    case 0x62: return ld(h, d);
    case 0x63: return ld(h, e);
    case 0x64: return ld(h, h);
    case 0x65: return ld(h, l);
    case 0x66: return ld(h, mmu.read(hl));
    case 0x67: return ld(h, a);
    case 0x68: return ld(l, b);
    case 0x69: return ld(l, c);
    case 0x6A: return ld(l, d);
    case 0x6B: return ld(l, e);
    case 0x6C: return ld(l, h);
    case 0x6D: return ld(l, l);
    case 0x6E: return ld(l, mmu.read(hl));
    case 0x6F: return ld(l, a);
    //case 0x70: return ld(mmu.read(hl), b);
    //case 0x71: return ld(mmu.read(hl), c);
    //case 0x72: return ld(mmu.read(hl), d);
    //case 0x73: return ld(mmu.read(hl), e);
    //case 0x74: return ld(mmu.read(hl), h);
    //case 0x75: return ld(mmu.read(hl), l);
    //case 0x77: return ld(mmu.read(hl),a);
    case 0x78: return ld(a, b);
    case 0x79: return ld(a, c);
    case 0x7A: return ld(a, d);
    case 0x7B: return ld(a, e);
    case 0x7C: return ld(a, h);
    case 0x7D: return ld(a, l);
    case 0x7E: return ld(a, mmu.read(hl));
    case 0x7F: return ld(a, a);
	case 0xAF: return xorn(a);
	case 0xA8: return xorn(b);
	case 0xA9: return xorn(c);
	case 0xAA: return xorn(d);
	case 0xAB: return xorn(e);
	case 0xAC: return xorn(h);
	case 0xAD: return xorn(l);
	case 0xAE: return xorn(mmu.read(hl));
    case 0xCB: return cb(next_byte());
    case 0xE0: return ldh_n_a(next_byte());
    case 0xE2: return ld_c_a();
    //case 0xEA: return ld(next_word(), a);
	case 0xEE: return xorn(next_byte());
    case 0xF0: return ldh_a_n(next_byte());
    case 0xF2: return ld_a_c();
    case 0xFA: return ld(a, mmu.read(next_word()));


	default:
		not_implemented(opcode);
	}
    // clang-format on
}


/* 8-Bit Loads */

void Cpu::ld(byte& r, byte n) {
    r = n;
}

void Cpu::ld_a_c() {
    word address = 0xFF00 + c;
    a = mmu.read(address);
}

void Cpu::ld_c_a() {
    word address = 0xFF00 + c;
    mmu.write(address, a);
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

void Cpu::ldh_a_n(byte n) {
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