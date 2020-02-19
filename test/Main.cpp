#define CATCH_CONFIG_MAIN
#include "lib/catch/catch.hpp"

#include <cpu.h>
#include <cartridge.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

TEST_CASE("Cartridge header can be read") {

    std::string romPath = "C:\\Users\\neil\\source\\repos\\Gameboy\\test\\resources\\blargg\\cpu_instrs.gb";

    using std::ifstream;
    using std::ios;

    ifstream stream(romPath, ios::binary | ios::ate);
    auto size = stream.tellg();
    std::vector<char> buffer(size);

    stream.seekg(0, ios::beg);
    stream.read(&buffer[0], size);
    stream.close();

    auto rom = std::vector<byte>(buffer.begin(), buffer.end());
    Cartridge cartridge(rom);

    REQUIRE(cartridge.title == "CPU_INSTRS");
    REQUIRE(cartridge.cgb_flag == CGBFlag::GB_AND_GBC);
    REQUIRE(cartridge.sgb_flag == SGBFlag::NORMAL);
    REQUIRE(cartridge.rom_size == ROMSize::ROM_64KB);
    REQUIRE(cartridge.ram_size == RAMSize::NONE);
}

