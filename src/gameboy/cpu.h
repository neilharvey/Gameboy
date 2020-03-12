#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

#include "mmu.h"
#include "types.h"

enum class Condition {
    NZ,
    Z,
    NC,
    C
};

enum class Flag : int {
    Z = 7,
    N = 6,
    H = 5,
    C = 4
};

class Cpu {

public:
    union {
        struct {
            byte f;
            byte a;
        };
        word af;
    };

    union {
        struct {
            byte c;
            byte b;
        };
        word bc;
    };

    union {
        struct {
            byte e;
            byte d;
        };
        word de;
    };

    union {
        struct {
            byte l;
            byte h;
        };
        word hl;
    };

    word pc;
    word sp;

    bool ime;
    bool halted;
    bool stopped;

    Cpu(Mmu& m);
    void tick();

    void execute_opcode(const byte& opcode);

private:
    Mmu& mmu;


    // 8-bit loads
    void ld(byte& r, byte n);
    void ld_a_c();
    void ld_c_a();
    void ldd_a_hl();
    void ldd_hl_a();
    void ldi_a_hl();
    void ldi_hl_a();
    void ldh_n_a(byte n);
    void ldh_a_n(byte n);
    void ld(word address, byte n);

    // 16-bit loads
    void ld(word& r, word nn);
    void ldhl_sp(byte n);
    void ld_nn_sp(word nn);
    void push(word nn);
    void pop(word& nn);

    // 8-bit Arithmetic
    void add(byte n);
    void adc(byte n);
    void sub(byte n);
    void sbc(byte n);
    void And(byte n);
    void Or(byte n);
    void Xor(byte n);
    void cp(byte n);
    void inc(byte& r);
    void inc_hl(); // TODO Refactor
    void dec(byte& r);
    void dec_hl(); // TOTO Refactor

    // 16-bit arithmetic
    void add_hl(word n);
    void add_sp(sbyte n);
    void inc(word& nn);
    void dec(word& nn);

    // misc
    void swap(byte& n);
    void swap(word address);
    void daa();
    void cpl();
    void ccf();
    void scf();
    void nop();
    void halt();
    void stop();
    void di();
    void ei();
    void cb(byte opcode);

    // rotates & Shifts
    void rlca();
    void rrca();
    void rla();
    void rra();
    void rlc(byte& reg);
    void rlc(word address);
    void rl(byte& reg);
    void rl(word address);
    void rrc(byte& reg);
    void rrc(word address);
    void rr(byte& reg);
    void rr(word address);
    void sla(byte& reg);
    void sla(word address);
    void sra(byte& reg);
    void sra(word address);
    void srl(byte& reg);
    void srl(word address);

    // bitwise
    void bit(int b, byte r);
    void set(int b, byte& r);
    void set(int b, word address);
    void res(int b, byte& r);
    void res(int b, word address);

    // jumps
    void jp(word nn);
    void jp(Condition cc, word nn);
    void jr(sbyte n);
    void jr(Condition cc, sbyte n);

    // calls
    void call(word nn);
    void call(Condition cc, word nn);

    // Restarts
    void rst(byte n);
    void ret();
    void ret(Condition cc);
    void reti();

    // memory
    byte read_byte(word address);
    void write_byte(word address, byte value);
    byte next_byte();
    sbyte next_signed_byte();
    word next_word();

    // flags
    bool get_flag(Flag flag);
    void set_flag(Flag flag, bool value);

    // utility
    bool test_condition(Condition cc);
    void not_implemented(byte opcode);
};
