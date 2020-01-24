#define CATCH_CONFIG_MAIN
#include "lib/catch/catch.hpp"

#include <cpu.h>
#include <iostream>
#include <iomanip>
#include <sstream>

TEST_CASE("Boot ROM can be run") {


    // TODO : Currently fails loading Nintendo logo due to lack of cartridge data

    std::unique_ptr<Mmu> mmu = std::make_unique<Mmu>();
    Cpu cpu(*mmu);
    while (cpu.pc <= 0x00A7)
    {
        std::cout << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << (int)cpu.pc << "\n";
        cpu.tick();
    }

}