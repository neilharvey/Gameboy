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
	void Tick();

private:
	Mmu& mmu;


};

