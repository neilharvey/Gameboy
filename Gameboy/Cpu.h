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

	//struct instruction
	//{
	//	const char* mneumonic;
	//	byte length;
	//	byte duration;
	//	void (Cpu::*)() action;
	//};

	//const struct instruction instructions[0xFF]{
	//	{ "NOP", 0, 0, &Cpu::nop }
	//};

	Mmu& mmu;

	void nop(void);
};

