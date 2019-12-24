#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "Bitwise.h"
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

    switch (opcode) {
    case 0x00: return nop();
    case 0x01: return ld(bc, next_word());
    case 0x02: return ld(bc, a);
    case 0x03: return inc(bc);
    case 0x04: return inc(b);
    case 0x05: return dec(b);
    case 0x0A: return ld(a, mmu.read(bc));
    case 0x06: return ld(b, next_byte());
    case 0x07: return rlca();
    case 0x08: return ld_nn_sp(next_word());
    case 0x09: return add_hl(bc);
    case 0x0B: return dec(bc);
    case 0x0C: return inc(c);
    case 0x0D: return dec(d);
    case 0x0E: return ld(c, next_byte());
    case 0x0F: return rrca();
    case 0x10: return stop();
    case 0x11: return ld(de, next_word());
    case 0x12: return ld(de, a);
    case 0x13: return inc(de);
    case 0x14: return inc(d);
    case 0x15: return dec(d);
    case 0x16: return ld(d, next_byte());
    case 0x17: return rla();
    case 0x19: return add_hl(de);
    case 0x1A: return ld(a, mmu.read(de));
    case 0x1B: return dec(de);
    case 0x1C: return inc(e);
    case 0x1D: return dec(e);
    case 0x1E: return ld(e, next_byte());
    case 0x1F: return rra();
    case 0x20: return jr(Condition::NZ, next_signed_byte());
    case 0x21: return ld(hl, next_word());
    case 0x22: return ldi_hl_a();
    case 0x23: return inc(hl);
    case 0x24: return inc(h);
    case 0x25: return dec(h);
    case 0x27: return daa();
    case 0x29: return add_hl(hl);
    case 0x2A: return ldi_a_hl();
    case 0x2B: return dec(hl);
    case 0x2C: return inc(l);
    case 0x2D: return dec(l);
    case 0x26: return ld(h, next_byte());
    case 0x2E: return ld(l, next_byte());
    case 0x2F: return cpl();
    case 0x31: return ld(sp, next_word());
    case 0x32: return ldd_hl_a();
    case 0x33: return inc(sp);
    case 0x34: return inc_hl();
    case 0x35: return dec_hl();
    case 0x36: return ld(hl, next_byte());
    case 0x37: return scf();
    case 0x39: return add_hl(sp);
    case 0x3A: return ldd_a_hl();
    case 0x3B: return dec(sp);
    case 0x3C: return inc(a);
    case 0x3D: return dec(a);
    case 0x3E: return ld(a, next_byte());
    case 0x3F: return ccf();
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
    case 0x70: return ld(hl, b);
    case 0x71: return ld(hl, c);
    case 0x72: return ld(hl, d);
    case 0x73: return ld(hl, e);
    case 0x74: return ld(hl, h);
    case 0x75: return ld(hl, l);
    case 0x76: return halt();
    case 0x77: return ld(hl, a);
    case 0x78: return ld(a, b);
    case 0x79: return ld(a, c);
    case 0x7A: return ld(a, d);
    case 0x7B: return ld(a, e);
    case 0x7C: return ld(a, h);
    case 0x7D: return ld(a, l);
    case 0x7E: return ld(a, mmu.read(hl));
    case 0x7F: return ld(a, a);
    case 0x80: return add(b);
    case 0x81: return add(c);
    case 0x82: return add(d);
    case 0x83: return add(e);
    case 0x84: return add(h);
    case 0x85: return add(l);
    case 0x86: return add(mmu.read(hl));
    case 0x87: return add(a);
    case 0x8F: return adc(a);
    case 0x88: return adc(b);
    case 0x89: return adc(c);
    case 0x8A: return adc(d);
    case 0x8B: return adc(e);
    case 0x8C: return adc(h);
    case 0x8D: return adc(l);
    case 0x8E: return adc(mmu.read(hl));
    case 0x90: return sub(b);
    case 0x91: return sub(c);
    case 0x92: return sub(d);
    case 0x93: return sub(e);
    case 0x94: return sub(h);
    case 0x95: return sub(l);
    case 0x96: return sub(mmu.read(hl));
    case 0x97: return sub(a);
    case 0x98: return sbc(b);
    case 0x99: return sbc(c);
    case 0x9A: return sbc(d);
    case 0x9B: return sbc(e);
    case 0x9C: return sbc(h);
    case 0x9D: return sbc(l);
    case 0x9E: return sbc(mmu.read(hl));
    case 0x9F: return sbc(a);
    case 0xA0: return And(b);
    case 0xA1: return And(c);
    case 0xA2: return And(d);
    case 0xA3: return And(e);
    case 0xA4: return And(h);
    case 0xA5: return And(l);
    case 0xA6: return And(mmu.read(hl));
    case 0xA7: return And(a);
    case 0xA8: return Xor(b);
    case 0xA9: return Xor(c);
    case 0xAA: return Xor(d);
    case 0xAB: return Xor(e);
    case 0xAC: return Xor(h);
    case 0xAD: return Xor(l);
    case 0xAE: return Xor(mmu.read(hl));
    case 0xAF: return Xor(a);
    case 0xB0: return Or(b);
    case 0xB1: return Or(c);
    case 0xB2: return Or(d);
    case 0xB3: return Or(e);
    case 0xB4: return Or(h);
    case 0xB5: return Or(l);
    case 0xB6: return Or(mmu.read(hl));
    case 0xB7: return Or(a);
    case 0xB8: return cp(b);
    case 0xB9: return cp(c);
    case 0xBA: return cp(d);
    case 0xBB: return cp(e);
    case 0xBC: return cp(h);
    case 0xBD: return cp(l);
    case 0xBE: return cp(mmu.read(hl));
    case 0xBF: return cp(a);
    case 0xC1: return pop(bc);
    case 0xC2: return jp(Condition::NZ, next_word());
    case 0xC3: return jp(next_word());
    case 0xC5: return push(bc);
    case 0xC6: return add(next_byte());
    case 0xCA: return jp(Condition::Z, next_word());
    case 0xCE: return adc(next_byte());
    case 0xCB: return cb(next_byte());
    case 0xD1: return pop(de);
    case 0xD2: return jp(Condition::NC, next_word());
    case 0xD5: return push(de);
    case 0xD6: return sub(next_byte());
    case 0xDA: return jp(Condition::C, next_word());
    case 0xE0: return ldh_n_a(next_byte());
    case 0xE1: return pop(hl);
    case 0xE2: return ld_c_a();
    case 0xE5: return push(hl);
    case 0xE6: return And(next_byte());
    case 0xE8: return add_sp(next_byte());
    case 0xE9: return jp(hl);
    case 0xEA: return ld(next_word(), a);
    case 0xEE: return Xor(next_byte());
    case 0xF0: return ldh_a_n(next_byte());
    case 0xF1: return pop(af);
    case 0xF2: return ld_a_c();
    case 0xF3: return di();
    case 0xF6: return Or(next_byte());
    case 0xF8: return ldhl_sp(next_byte());
    case 0xFA: return ld(a, mmu.read(next_word()));
    case 0xFB: return ei();
    case 0xF5: return push(af);
    case 0xF9: return ld(sp, hl);
    case 0xFE: return cp(next_byte());
    default:
        not_implemented(opcode);
    }
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
    a = mmu.read(hl);
    hl--;
}

void Cpu::ldd_hl_a() {
    mmu.write(hl, a);
    hl--;
}

void Cpu::ldi_a_hl() {
    a = mmu.read(hl);
    hl++;
}

void Cpu::ldi_hl_a() {
    mmu.write(hl, a);
    hl++;
}

void Cpu::ldh_n_a(byte n) {
    word address = 0xFF00 + n;
    mmu.write(address, a);
}

void Cpu::ldh_a_n(byte n) {
    word address = 0xFF00 + n;
    a = mmu.read(address);
}

void Cpu::ld(word address, byte n) {
    mmu.write(address, n);
}

/* 16-Bit Loads */

void Cpu::ld(word& r, word nn) {
    r = nn;
}

void Cpu::ldhl_sp(byte n) {
    hl = sp + n;
}

void Cpu::ld_nn_sp(word address) {

    mmu.write(address, bitwise::get_lsb(sp));
    mmu.write(address + 1, bitwise::get_msb(sp));
}

void Cpu::push(word nn) {

    mmu.write(--sp, bitwise::get_msb(nn));
    mmu.write(--sp, bitwise::get_lsb(nn));
}

void Cpu::pop(word& nn) {

    byte lsb = mmu.read(sp++);
    byte msb = mmu.read(sp++);

    nn = (msb << 8) + lsb;
}

void Cpu::add(byte n) {
}

void Cpu::adc(byte n) {
}

void Cpu::sub(byte n) {
}

void Cpu::sbc(byte n) {
}

void Cpu::And(byte n) {
}

void Cpu::Or(byte n) {
}

/* 8-Bit Arithmetic */

void Cpu::Xor(byte n) {
    byte result = a ^ n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, false);

    a = result;
}

void Cpu::cp(byte n) {
}

void Cpu::inc(byte& r) {
}

void Cpu::inc_hl() {
}

/* 16-Bit Arithmetic */

void Cpu::add_hl(word n) {
}

void Cpu::add_sp(byte n) {
}

void Cpu::inc(word& address) {
}

void Cpu::dec(byte& r) {
}

void Cpu::dec_hl() {
}

void Cpu::dec(word& address) {
}

void Cpu::swap(byte& n) {
}

void Cpu::swap(word address) {

    byte value = mmu.read(address);
    swap(value);
    mmu.write(address, value);
}

void Cpu::daa() {
}

void Cpu::cpl() {

    a = ~a;
    set_flag(Flag::N, true);
    set_flag(Flag::H, true);
}

void Cpu::ccf() {

    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, !get_flag(Flag::C));
}

void Cpu::scf() {
}

/* Misc */

void Cpu::nop() {}

void Cpu::halt() {
}

void Cpu::stop() {
}

void Cpu::di() {
}

void Cpu::ei() {
}

void Cpu::cb(byte opcode) {
    switch (opcode) {
    case 0x30: return swap(b);
    case 0x31: return swap(c);
    case 0x32: return swap(d);
    case 0x33: return swap(e);
    case 0x34: return swap(h);
    case 0x35: return swap(l);
    case 0x36: return swap(hl);
    case 0x37: return swap(a);
    case 0x7C: return bit(7, h);
    default:
        not_implemented(opcode);
    }
}

void Cpu::rlca() {
}

void Cpu::rla() {
}

void Cpu::rrca() {
}

void Cpu::rra() {
}

void Cpu::rlc(byte n) {
}

void Cpu::rl(byte b) {
}

void Cpu::rrc(byte n) {
}

void Cpu::rr(byte n) {
}

void Cpu::sla(byte n) {
}

void Cpu::sra(byte n) {
}

void Cpu::srl(byte n) {
}

void Cpu::bit(int b, byte r) {

    bool result = bitwise::is_bit_set(r, b);

    set_flag(Flag::Z, !result);
    set_flag(Flag::N, false);
    set_flag(Flag::H, true);
}

void Cpu::set(int b, byte& r) {
}

void Cpu::res(int b, byte& r) {
}

void Cpu::jp(word nn) {
}

void Cpu::jp(Condition cc, word nn) {
}

void Cpu::jr(sbyte n) {
    pc = pc + n;
}

void Cpu::jr(Condition cc, sbyte n) {
    if (test_condition(cc)) {
        jr(n);
    }
}

void Cpu::call(word nn) {
}

void Cpu::call(Condition cc, word nn) {
}

void Cpu::rst(byte n) {
}

void Cpu::ret() {
}

void Cpu::ret(Condition cc) {
}

void Cpu::reti() {
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