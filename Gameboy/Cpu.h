#pragma once
#include "Mmu.h"
#include "Types.h"

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
            byte a;
            byte f;
        };
        word af;
    };

    union {
        struct {
            byte b;
            byte c;
        };
        word bc;
    };

    union {
        struct {
            byte d;
            byte e;
        };
        word de;
    };

    union {
        struct {
            byte h;
            byte l;
        };
        word hl;
    };

    word pc;
    word sp;

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
    void inc_hl();
    void dec(byte& r);
    void dec_hl();

    // 16-bit arithmetic
    void add_hl(word n);
    void add_sp(byte n);
    void inc(word& r);
    void dec(word& r);

    // Misc
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
    void rla();
    void rrca();
    void rra();
    void rlc(byte n);
    void rl(byte b);
    void rrc(byte n);
    void rr(byte n);
    void sla(byte n);
    void sra(byte n);
    void srl(byte n);

    // bitwise
    void bit(int b, byte r);
    void set(int b, byte& r);
    void res(int b, byte& r);

    //// jumps
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
