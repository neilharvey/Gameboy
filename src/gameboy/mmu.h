#pragma once

#include <vector>

#include "bootrom.h"
#include "cartridge.h"
#include "ppu.h"
#include "types.h"

class Mmu
{
public:
    Mmu(Ppu& ppu, std::vector<byte>& ram, Cartridge& cartridge);
    byte read(word address);
    void write(word address, byte value);
private:
    bool booting;
    Cartridge& cartridge;
    Ppu& ppu;
    std::vector<byte>& ram;
};

