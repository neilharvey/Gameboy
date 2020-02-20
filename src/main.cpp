#include "Main.h"

int main()
{
    std::string romPath = "../../../../test/resources/blargg/cpu_instrs.gb";

    auto cartridge = Cartridge::load(romPath);

    std::cout << cartridge.title << '\n';
}
