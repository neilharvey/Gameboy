#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "Bitwise.h"
#include "Cpu.h"

using bitwise::clear_bit;
using bitwise::get_lsb;
using bitwise::get_msb;
using bitwise::is_bit_set;
using bitwise::set_bit;

Cpu::Cpu(Mmu& m) : mmu(m) {
    
    af = 0;
    bc = 0;
    de = 0;
    hl = 0;
    sp = 0;
    pc = 0;

    ime = true;
    halted = false;
    stopped = false;
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
    case 0x06: return ld(b, next_byte());
    case 0x07: return rlca();
    case 0x08: return ld_nn_sp(next_word());
    case 0x09: return add_hl(bc);
    case 0x0A: return ld(a, read_byte(bc));
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
    case 0x18: return jr(next_signed_byte());
    case 0x19: return add_hl(de);
    case 0x1A: return ld(a, read_byte(de));
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
    case 0x26: return ld(h, next_byte());
    case 0x27: return daa();
    case 0x28: return jr(Condition::Z, next_signed_byte());
    case 0x29: return add_hl(hl);
    case 0x2A: return ldi_a_hl();
    case 0x2B: return dec(hl);
    case 0x2C: return inc(l);
    case 0x2D: return dec(l);
    case 0x2E: return ld(l, next_byte());
    case 0x2F: return cpl();

    case 0x30: return jr(Condition::NC, next_signed_byte());
    case 0x31: return ld(sp, next_word());
    case 0x32: return ldd_hl_a();
    case 0x33: return inc(sp);
    case 0x34: return inc_hl();
    case 0x35: return dec_hl();
    case 0x36: return ld(hl, next_byte());
    case 0x37: return scf();
    case 0x38: return jr(Condition::C, next_signed_byte());
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
    case 0x46: return ld(b, read_byte(hl));
    case 0x47: return ld(b, a);
    case 0x48: return ld(c, b);
    case 0x49: return ld(c, c);
    case 0x4A: return ld(c, d);
    case 0x4B: return ld(c, e);
    case 0x4C: return ld(c, h);
    case 0x4D: return ld(c, l);
    case 0x4E: return ld(c, read_byte(hl));
    case 0x4F: return ld(c, a);

    case 0x50: return ld(d, b);
    case 0x51: return ld(d, c);
    case 0x52: return ld(d, d);
    case 0x53: return ld(d, e);
    case 0x54: return ld(d, h);
    case 0x55: return ld(d, l);
    case 0x56: return ld(d, read_byte(hl));
    case 0x57: return ld(d, a);
    case 0x58: return ld(e, b);
    case 0x59: return ld(e, c);
    case 0x5A: return ld(e, d);
    case 0x5B: return ld(e, e);
    case 0x5C: return ld(e, h);
    case 0x5D: return ld(e, l);
    case 0x5E: return ld(e, read_byte(hl));
    case 0x5F: return ld(e, a);

    case 0x60: return ld(h, b);
    case 0x61: return ld(h, c);
    case 0x62: return ld(h, d);
    case 0x63: return ld(h, e);
    case 0x64: return ld(h, h);
    case 0x65: return ld(h, l);
    case 0x66: return ld(h, read_byte(hl));
    case 0x67: return ld(h, a);
    case 0x68: return ld(l, b);
    case 0x69: return ld(l, c);
    case 0x6A: return ld(l, d);
    case 0x6B: return ld(l, e);
    case 0x6C: return ld(l, h);
    case 0x6D: return ld(l, l);
    case 0x6E: return ld(l, read_byte(hl));
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
    case 0x7E: return ld(a, read_byte(hl));
    case 0x7F: return ld(a, a);

    case 0x80: return add(b);
    case 0x81: return add(c);
    case 0x82: return add(d);
    case 0x83: return add(e);
    case 0x84: return add(h);
    case 0x85: return add(l);
    case 0x86: return add(read_byte(hl));
    case 0x87: return add(a);
    case 0x88: return adc(b);
    case 0x89: return adc(c);
    case 0x8A: return adc(d);
    case 0x8B: return adc(e);
    case 0x8C: return adc(h);
    case 0x8D: return adc(l);
    case 0x8E: return adc(read_byte(hl));
    case 0x8F: return adc(a);

    case 0x90: return sub(b);
    case 0x91: return sub(c);
    case 0x92: return sub(d);
    case 0x93: return sub(e);
    case 0x94: return sub(h);
    case 0x95: return sub(l);
    case 0x96: return sub(read_byte(hl));
    case 0x97: return sub(a);
    case 0x98: return sbc(b);
    case 0x99: return sbc(c);
    case 0x9A: return sbc(d);
    case 0x9B: return sbc(e);
    case 0x9C: return sbc(h);
    case 0x9D: return sbc(l);
    case 0x9E: return sbc(read_byte(hl));
    case 0x9F: return sbc(a);

    case 0xA0: return And(b);
    case 0xA1: return And(c);
    case 0xA2: return And(d);
    case 0xA3: return And(e);
    case 0xA4: return And(h);
    case 0xA5: return And(l);
    case 0xA6: return And(read_byte(hl));
    case 0xA7: return And(a);
    case 0xA8: return Xor(b);
    case 0xA9: return Xor(c);
    case 0xAA: return Xor(d);
    case 0xAB: return Xor(e);
    case 0xAC: return Xor(h);
    case 0xAD: return Xor(l);
    case 0xAE: return Xor(read_byte(hl));
    case 0xAF: return Xor(a);

    case 0xB0: return Or(b);
    case 0xB1: return Or(c);
    case 0xB2: return Or(d);
    case 0xB3: return Or(e);
    case 0xB4: return Or(h);
    case 0xB5: return Or(l);
    case 0xB6: return Or(read_byte(hl));
    case 0xB7: return Or(a);
    case 0xB8: return cp(b);
    case 0xB9: return cp(c);
    case 0xBA: return cp(d);
    case 0xBB: return cp(e);
    case 0xBC: return cp(h);
    case 0xBD: return cp(l);
    case 0xBE: return cp(read_byte(hl));
    case 0xBF: return cp(a);

    case 0xC0: return ret(Condition::NZ);
    case 0xC1: return pop(bc);
    case 0xC2: return jp(Condition::NZ, next_word());
    case 0xC3: return jp(next_word());
    case 0xC4: return call(Condition::NZ, next_word());
    case 0xC5: return push(bc);
    case 0xC6: return add(next_byte());
    case 0xC7: return rst(0x00);
    case 0xC8: return ret(Condition::Z);
    case 0xC9: return ret();
    case 0xCA: return jp(Condition::Z, next_word());
    case 0xCB: return cb(next_byte());
    case 0xCC: return call(Condition::Z, next_word());
    case 0xCD: return call(next_word());
    case 0xCE: return adc(next_byte());
    case 0xCF: return rst(0x08);

    case 0xD0: return ret(Condition::NC);
    case 0xD1: return pop(de);
    case 0xD2: return jp(Condition::NC, next_word());
    case 0xD5: return push(de);
    case 0xD6: return sub(next_byte());
    case 0xD7: return rst(0x10);
    case 0xD8: return ret(Condition::C);
    case 0xD9: return reti();
    case 0xDA: return jp(Condition::C, next_word());
    case 0xDC: return call(Condition::C, next_word());
    case 0xDE: return sbc(next_byte());
    case 0xDF: return rst(0x18);

    case 0xE0: return ldh_n_a(next_byte());
    case 0xE1: return pop(hl);
    case 0xE2: return ld_c_a();
    case 0xE5: return push(hl);
    case 0xE6: return And(next_byte());
    case 0xE7: return rst(0x20);
    case 0xE8: return add_sp(next_byte());
    case 0xE9: return jp(hl);
    case 0xEA: return ld(next_word(), a);
    case 0xEE: return Xor(next_byte());
    case 0xEF: return rst(0x28);

    case 0xF0: return ldh_a_n(next_byte());
    case 0xF1: return pop(af);
    case 0xF2: return ld_a_c();
    case 0xF3: return di();
    case 0xF5: return push(af);
    case 0xF6: return Or(next_byte());
    case 0xF7: return rst(0x30);
    case 0xF8: return ldhl_sp(next_byte());
    case 0xF9: return ld(sp, hl);
    case 0xFA: return ld(a, read_byte(next_word()));
    case 0xFB: return ei();
    case 0xFE: return cp(next_byte());
    case 0xFF: return rst(0x38);

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
    a = read_byte(address);
}

void Cpu::ld_c_a() {
    word address = 0xFF00 + c;
    mmu.write(address, a);
}

void Cpu::ldd_a_hl() {
    a = read_byte(hl);
    hl--;
}

void Cpu::ldd_hl_a() {
    mmu.write(hl, a);
    hl--;
}

void Cpu::ldi_a_hl() {
    a = read_byte(hl);
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
    a = read_byte(address);
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

    mmu.write(address, get_lsb(sp));
    mmu.write(address + 1, get_msb(sp));
}

void Cpu::push(word nn) {

    mmu.write(--sp, get_msb(nn));
    mmu.write(--sp, get_lsb(nn));
}

void Cpu::pop(word& nn) {

    byte lsb = read_byte(sp++);
    byte msb = read_byte(sp++);

    nn = (msb << 8) + lsb;
}

/* 8-Bit Arithmetic */

void Cpu::add(byte n) {

    int result = a + n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, (a & 0xF) + (n & 0xF) > 0xF);
    set_flag(Flag::C, result > 0xFf);

    a = static_cast<byte>(result);
}

void Cpu::adc(byte n) {

    int c = get_flag(Flag::C) ? 1 : 0;
    int result = a + n + c;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, (a & 0xF) + (n & 0xF) + c > 0xF);
    set_flag(Flag::C, result > 0xFf);

    a = static_cast<byte>(result);
}

void Cpu::sub(byte n) {

    int result = a - n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, true);
    set_flag(Flag::H, (a & 0xF) - (n & 0xF) < 0);
    set_flag(Flag::C, a < n);

    a = static_cast<byte>(result);
}

void Cpu::sbc(byte n) {
}

void Cpu::And(byte n) {

    byte result = a & n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, true);
    set_flag(Flag::C, false);

    a = result;
}

void Cpu::Or(byte n) {

    byte result = a | n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, false);

    a = result;
}

void Cpu::Xor(byte n) {

    byte result = a ^ n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, false);

    a = result;
}

void Cpu::cp(byte n) {

    int result = a - n;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, true);
    set_flag(Flag::H, (a & 0xF) - (n & 0xF) < 0);
    set_flag(Flag::C, a < n);
}

void Cpu::inc(byte& n) {

    byte result = n + 1;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, (result & 0x0F) == 0x00);

    n = result;
}

void Cpu::dec(byte& n) {

    int result = n - 1;

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, true);
    set_flag(Flag::H, (result & 0x0F) == 0x0F);
}

void Cpu::dec_hl() {

    byte value = read_byte(hl);
    dec(value);
    write_byte(hl, value);
}

void Cpu::inc_hl() {

    byte value = read_byte(hl);
    inc(value);
    write_byte(hl, value);
}

/* 16-Bit Arithmetic */

void Cpu::add_hl(word n) {

    int result = hl + n;

    set_flag(Flag::N, false);
    set_flag(Flag::H, (hl & 0xFFF) + (result & 0xFFF) > 0xFFF);
    set_flag(Flag::C, result > 0xFFFF);

    hl = static_cast<word>(result);
}

void Cpu::add_sp(sbyte n) {

    int result = sp + n;

    set_flag(Flag::Z, false);
    set_flag(Flag::N, false);
    // set_flag(Flag::H, ????); // Set or reset according to operation.?
    // set_flag(Flag::C, ????);

    sp = result;
}

void Cpu::inc(word& nn) {
    nn++;
}

void Cpu::dec(word& nn) {
    nn--;
}


// TODO
void Cpu::swap(byte& n) {

    int result = 0; // Swap upper & lower nibles of n

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, false);

    n = result;
}

/* Misc */

void Cpu::swap(word address) {

    byte value = read_byte(address);
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

    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, true);
}

void Cpu::nop() {}

void Cpu::halt() {
    halted = true;
    // TODO : Implement HALT skip bug
}

void Cpu::stop() {
    stopped = true;
}

void Cpu::di() {
    ime = false;
    // TODO: Needs to be disabled AFTER next instruction
}

void Cpu::ei() {
    ime = true;
    // TODO: Needs to be enabled AFTER next instruction
}

void Cpu::cb(byte opcode) {
    switch (opcode) {

    case 0x00: return rlc(b);
    case 0x01: return rlc(c);
    case 0x02: return rlc(d);
    case 0x03: return rlc(e);
    case 0x04: return rlc(h);
    case 0x05: return rlc(l);
    case 0x06: return rlc(hl);
    case 0x07: return rlc(a);
    case 0x08: return rrc(b);
    case 0x09: return rrc(c);
    case 0x0A: return rrc(d);
    case 0x0B: return rrc(e);
    case 0x0C: return rrc(h);
    case 0x0D: return rrc(l);
    case 0x0E: return rrc(hl);
    case 0x0F: return rrc(a);

    case 0x10: return rl(b);
    case 0x11: return rl(c);
    case 0x12: return rl(d);
    case 0x13: return rl(e);
    case 0x14: return rl(h);
    case 0x15: return rl(l);
    case 0x16: return rl(hl);
    case 0x17: return rl(a);
    case 0x18: return rr(b);
    case 0x19: return rr(c);
    case 0x1A: return rr(d);
    case 0x1B: return rr(e);
    case 0x1C: return rr(h);
    case 0x1D: return rr(l);
    case 0x1E: return rr(hl);
    case 0x1F: return rr(a);

    case 0x20: return sla(b);
    case 0x21: return sla(c);
    case 0x22: return sla(d);
    case 0x23: return sla(e);
    case 0x24: return sla(h);
    case 0x25: return sla(l);
    case 0x26: return sla(hl);
    case 0x27: return sla(a);
    case 0x28: return sra(b);
    case 0x29: return sra(c);
    case 0x2A: return sra(d);
    case 0x2B: return sra(e);
    case 0x2C: return sra(h);
    case 0x2D: return sra(l);
    case 0x2E: return sra(hl);
    case 0x2F: return sra(a);

    case 0x30: return swap(b);
    case 0x31: return swap(c);
    case 0x32: return swap(d);
    case 0x33: return swap(e);
    case 0x34: return swap(h);
    case 0x35: return swap(l);
    case 0x36: return swap(hl);
    case 0x37: return swap(a);
    case 0x38: return srl(b);
    case 0x39: return srl(c);
    case 0x3A: return srl(d);
    case 0x3B: return srl(e);
    case 0x3C: return srl(h);
    case 0x3D: return srl(l);
    case 0x3E: return srl(hl);
    case 0x3F: return srl(a);

    case 0x40: return bit(0, b);
    case 0x41: return bit(0, c);
    case 0x42: return bit(0, d);
    case 0x43: return bit(0, e);
    case 0x44: return bit(0, h);
    case 0x45: return bit(0, l);
    case 0x46: return bit(0, read_byte(hl));
    case 0x47: return bit(0, a);
    case 0x48: return bit(1, b);
    case 0x49: return bit(1, c);
    case 0x4A: return bit(1, d);
    case 0x4B: return bit(1, e);
    case 0x4C: return bit(1, h);
    case 0x4D: return bit(1, l);
    case 0x4E: return bit(1, read_byte(hl));
    case 0x4F: return bit(1, a);

    case 0x50: return bit(2, b);
    case 0x51: return bit(2, c);
    case 0x52: return bit(2, d);
    case 0x53: return bit(2, e);
    case 0x54: return bit(2, h);
    case 0x55: return bit(2, l);
    case 0x56: return bit(2, read_byte(hl));
    case 0x57: return bit(2, a);
    case 0x58: return bit(3, b);
    case 0x59: return bit(3, c);
    case 0x5A: return bit(3, d);
    case 0x5B: return bit(3, e);
    case 0x5C: return bit(3, h);
    case 0x5D: return bit(3, l);
    case 0x5E: return bit(3, read_byte(hl));
    case 0x5F: return bit(3, a);

    case 0x60: return bit(4, b);
    case 0x61: return bit(4, c);
    case 0x62: return bit(4, d);
    case 0x63: return bit(4, e);
    case 0x64: return bit(4, h);
    case 0x65: return bit(4, l);
    case 0x66: return bit(4, read_byte(hl));
    case 0x67: return bit(4, a);
    case 0x68: return bit(5, b);
    case 0x69: return bit(5, c);
    case 0x6A: return bit(5, d);
    case 0x6B: return bit(5, e);
    case 0x6C: return bit(5, h);
    case 0x6D: return bit(5, l);
    case 0x6E: return bit(5, read_byte(hl));
    case 0x6F: return bit(5, a);

    case 0x70: return bit(6, b);
    case 0x71: return bit(6, c);
    case 0x72: return bit(6, d);
    case 0x73: return bit(6, e);
    case 0x74: return bit(6, h);
    case 0x75: return bit(6, l);
    case 0x76: return bit(6, read_byte(hl));
    case 0x77: return bit(6, a);
    case 0x78: return bit(7, b);
    case 0x79: return bit(7, c);
    case 0x7A: return bit(7, d);
    case 0x7B: return bit(7, e);
    case 0x7C: return bit(7, h);
    case 0x7D: return bit(7, l);
    case 0x7E: return bit(7, read_byte(hl));
    case 0x7F: return bit(7, a);

    case 0x80: return res(0, b);
    case 0x81: return res(0, c);
    case 0x82: return res(0, d);
    case 0x83: return res(0, e);
    case 0x84: return res(0, h);
    case 0x85: return res(0, l);
    case 0x86: return res(0, hl);
    case 0x87: return res(0, a);
    case 0x88: return res(1, b);
    case 0x89: return res(1, c);
    case 0x8A: return res(1, d);
    case 0x8B: return res(1, e);
    case 0x8C: return res(1, h);
    case 0x8D: return res(1, l);
    case 0x8E: return res(1, hl);
    case 0x8F: return res(1, a);

    case 0x90: return res(2, b);
    case 0x91: return res(2, c);
    case 0x92: return res(2, d);
    case 0x93: return res(2, e);
    case 0x94: return res(2, h);
    case 0x95: return res(2, l);
    case 0x96: return res(2, hl);
    case 0x97: return res(2, a);
    case 0x98: return res(3, b);
    case 0x99: return res(3, c);
    case 0x9A: return res(3, d);
    case 0x9B: return res(3, e);
    case 0x9C: return res(3, h);
    case 0x9D: return res(3, l);
    case 0x9E: return res(3, hl);
    case 0x9F: return res(3, a);

    case 0xA0: return res(4, b);
    case 0xA1: return res(4, c);
    case 0xA2: return res(4, d);
    case 0xA3: return res(4, e);
    case 0xA4: return res(4, h);
    case 0xA5: return res(4, l);
    case 0xA6: return res(4, hl);
    case 0xA7: return res(4, a);
    case 0xA8: return res(5, b);
    case 0xA9: return res(5, c);
    case 0xAA: return res(5, d);
    case 0xAB: return res(5, e);
    case 0xAC: return res(5, h);
    case 0xAD: return res(5, l);
    case 0xAE: return res(5, hl);
    case 0xAF: return res(5, a);

    case 0xB0: return res(6, b);
    case 0xB1: return res(6, c);
    case 0xB2: return res(6, d);
    case 0xB3: return res(6, e);
    case 0xB4: return res(6, h);
    case 0xB5: return res(6, l);
    case 0xB6: return res(6, hl);
    case 0xB7: return res(6, a);
    case 0xB8: return res(7, b);
    case 0xB9: return res(7, c);
    case 0xBA: return res(7, d);
    case 0xBB: return res(7, e);
    case 0xBC: return res(7, h);
    case 0xBD: return res(7, l);
    case 0xBE: return res(7, hl);
    case 0xBF: return res(7, a);

    case 0xC0: return set(0, b);
    case 0xC1: return set(0, c);
    case 0xC2: return set(0, d);
    case 0xC3: return set(0, e);
    case 0xC4: return set(0, h);
    case 0xC5: return set(0, l);
    case 0xC6: return set(0, hl);
    case 0xC7: return set(0, a);
    case 0xC8: return set(1, b);
    case 0xC9: return set(1, c);
    case 0xCA: return set(1, d);
    case 0xCB: return set(1, e);
    case 0xCC: return set(1, h);
    case 0xCD: return set(1, l);
    case 0xCE: return set(1, hl);
    case 0xCF: return set(1, a);

    case 0xD0: return set(2, b);
    case 0xD1: return set(2, c);
    case 0xD2: return set(2, d);
    case 0xD3: return set(2, e);
    case 0xD4: return set(2, h);
    case 0xD5: return set(2, l);
    case 0xD6: return set(2, hl);
    case 0xD7: return set(2, a);
    case 0xD8: return set(3, b);
    case 0xD9: return set(3, c);
    case 0xDA: return set(3, d);
    case 0xDB: return set(3, e);
    case 0xDC: return set(3, h);
    case 0xDD: return set(3, l);
    case 0xDE: return set(3, hl);
    case 0xDF: return set(3, a);

    case 0xE0: return set(4, b);
    case 0xE1: return set(4, c);
    case 0xE2: return set(4, d);
    case 0xE3: return set(4, e);
    case 0xE4: return set(4, h);
    case 0xE5: return set(4, l);
    case 0xE6: return set(4, hl);
    case 0xE7: return set(4, a);
    case 0xE8: return set(5, b);
    case 0xE9: return set(5, c);
    case 0xEA: return set(5, d);
    case 0xEB: return set(5, e);
    case 0xEC: return set(5, h);
    case 0xED: return set(5, l);
    case 0xEE: return set(5, hl);
    case 0xEF: return set(5, a);

    case 0xF0: return set(6, b);
    case 0xF1: return set(6, c);
    case 0xF2: return set(6, d);
    case 0xF3: return set(6, e);
    case 0xF4: return set(6, h);
    case 0xF5: return set(6, l);
    case 0xF6: return set(6, hl);
    case 0xF7: return set(6, a);
    case 0xF8: return set(7, b);
    case 0xF9: return set(7, c);
    case 0xFA: return set(7, d);
    case 0xFB: return set(7, e);
    case 0xFC: return set(7, h);
    case 0xFD: return set(7, l);
    case 0xFE: return set(7, hl);
    case 0xFF: return set(7, a);

    default:
        not_implemented(opcode);
    }
}

/* Rotates & Shifts */

void Cpu::rlca() {
    rlc(a);
}

void Cpu::rrca() {
    rrc(a);
}

void Cpu::rla() {
    rl(a);
}

void Cpu::rra() {
    rr(a);
}

void Cpu::rlc(byte& reg) {

    bool carry = is_bit_set(reg, 7);

    byte result = reg << 1;
    result = carry ? set_bit(result, 0) : clear_bit(result, 0);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, carry);

    reg = result;
}

void Cpu::rlc(word address) {

    byte value = mmu.read(address);
    rlc(value);
    mmu.write(address, value);
}

void Cpu::rl(byte& reg) {

    bool carry = get_flag(Flag::C);
    set_flag(Flag::C, is_bit_set(reg, 7));

    byte result = reg << 1;
    result = carry ? set_bit(result, 0) : clear_bit(result, 0);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);    

    reg = result;
}

void Cpu::rl(word address) {

    byte value = mmu.read(address);
    rl(value);
    mmu.write(address, value);
}

void Cpu::rrc(byte& reg) {

    bool carry = is_bit_set(reg, 0);

    byte result = reg >> 1;
    result = carry ? set_bit(result, 7) : clear_bit(result, 7);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, carry);

    reg = result;
}

void Cpu::rrc(word address) {

    byte value = mmu.read(address);
    rrc(value);
    mmu.write(address, value);
}

void Cpu::rr(byte& reg) {

    bool carry = get_flag(Flag::C);
    set_flag(Flag::C, is_bit_set(reg, 0));

    byte result = reg >> 1;
    result = carry ? set_bit(result, 7) : clear_bit(result, 7);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);   

    reg = result;
}

void Cpu::rr(word address) {

    byte value = mmu.read(address);
    rr(value);
    mmu.write(address, value);
}

void Cpu::sla(byte& reg) {

    bool carry = is_bit_set(reg, 7);
    byte result = reg << 1;
    result = clear_bit(result, 0);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, carry);

    reg = result;
}

void Cpu::sla(word address) {

    byte value = mmu.read(address);
    sla(value);
    mmu.write(address, value);
}

void Cpu::sra(byte& reg) {

    bool carry = is_bit_set(reg, 0);
    bool msb = is_bit_set(reg, 7);
    
    byte result = reg >> 1;
    result = msb ? set_bit(result, 7) : clear_bit(result, 7);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, carry);

    reg = result;
}

void Cpu::sra(word address) {

    byte value = mmu.read(address);
    sra(value);
    mmu.write(address, value);
}

void Cpu::srl(byte& reg) {

    bool carry = is_bit_set(reg, 0);
    byte result = reg >> 1;
    result = clear_bit(result, 7);

    set_flag(Flag::Z, result == 0);
    set_flag(Flag::N, false);
    set_flag(Flag::H, false);
    set_flag(Flag::C, carry);

    reg = result;
}

void Cpu::srl(word address) {

    byte value = read_byte(address);
    srl(value);
    write_byte(address, value);
}

/* Bitwise */

void Cpu::bit(int b, byte r) {

    bool result = is_bit_set(r, b);

    set_flag(Flag::Z, !result);
    set_flag(Flag::N, false);
    set_flag(Flag::H, true);
}

void Cpu::set(int b, byte& r) {
    r = set_bit(r, b);
}

void Cpu::set(int b, word address) {

    byte value = read_byte(address);
    set(b, value);
    write_byte(address, value);
}

void Cpu::res(int b, byte& r) {
    r = clear_bit(r, b);
}

void Cpu::res(int b, word address) {

    byte value = read_byte(address);
    res(b, value);
    write_byte(address, value);
}

void Cpu::jp(word nn) {
    pc = nn;
}

void Cpu::jp(Condition cc, word nn) {
    if (test_condition(cc)) {
        jp(nn);
    }
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

    mmu.write(--sp, get_msb(pc));
    mmu.write(--sp, get_lsb(pc));
    pc = nn;
}

void Cpu::call(Condition cc, word nn) {

    if (test_condition(cc)) {
        call(nn);
    }
}

void Cpu::rst(byte n) {

    mmu.write(--sp, get_msb(pc));
    mmu.write(--sp, get_lsb(pc));
    pc = n;
}

void Cpu::ret() {
    pop(pc);
}

void Cpu::ret(Condition cc) {

    if (test_condition(cc)) {
        ret();
    }
}

void Cpu::reti() {
    ret();
    ei();
}

byte Cpu::read_byte(word address) {
    return mmu.read(address);
}

void Cpu::write_byte(word address, byte value) {
    mmu.write(address, value);
}

byte Cpu::next_byte() {
    return read_byte(pc++);
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
    return is_bit_set(f, (int)flag);
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
    default:
        return false;
    }
}

void Cpu::not_implemented(byte opcode) {
    std::stringstream ss;
    ss << "unknown opcode 0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)opcode;
    throw std::out_of_range(ss.str());
}