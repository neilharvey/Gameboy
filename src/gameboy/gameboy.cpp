#include "gameboy.h"

Gameboy::Gameboy(Cartridge& cartridge) :
    display(),
    ram(),
    ppu(ram, display),
    mmu(ppu, ram, cartridge),
    cpu(mmu)
{
}

void Gameboy::run()
{
    while (cpu.pc != 0x100) {
        cpu.tick();
        ppu.tick();
    }
}
