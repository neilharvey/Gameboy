#include "Main.h"

int main()
{
    std::string romPath = "../../../../test/resources/blargg/cpu_instrs.gb";
    auto cartridge = Cartridge::load(romPath);
    std::cout << cartridge.title << '\n';
    int counter = 0;

    try
    {
        std::unique_ptr<Mmu> mmu = std::make_unique<Mmu>(cartridge);
        Cpu cpu(*mmu);
        while (cpu.pc < 0x0100 && counter++ < 10000)
        {
            std::cout << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << (int)cpu.pc << "\n";
            cpu.tick();
        }
    }
    catch (const std::out_of_range & oor)
    {
        std::cout << oor.what() << '\n';
    }

}
