#pragma once
#include "Mmu.h"
#include "Types.h"

class Cpu
{
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

	// instructions
	void nop(void);
	void ld_r_n(&byte r, byte n);
	void ld_n_nn(word& reg, word nn);

	void ld_a_n(byte n);

	// memory
	byte read_byte();
	word read_word();
};

