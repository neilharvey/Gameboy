#include <cartridge.h>

#include "lib/catch/catch.hpp"

TEST_CASE("Cartridge header can be read", "[Cartridge]") {

    // test exe will be in out\build\target\test
    std::string romPath = "../../../../test/resources/blargg/cpu_instrs.gb";

    auto cartridge = Cartridge::load(romPath);

    REQUIRE(cartridge.title == "CPU_INSTRS");
    REQUIRE(cartridge.cgb_flag == CGBFlag::GB_AND_GBC);
    REQUIRE(cartridge.sgb_flag == SGBFlag::NORMAL);
    REQUIRE(cartridge.rom_size == ROMSize::ROM_64KB);
    REQUIRE(cartridge.ram_size == RAMSize::NONE);
}