#include <iostream>
#include "Cpu.h"
#include "Mmu.h"

int main()
{
    try
    {
        std::unique_ptr<Mmu> mmu = std::make_unique<Mmu>();
        Cpu cpu(*mmu);
        while (cpu.pc < 0x0100)
        {
            cpu.tick();
        }
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << oor.what() << '\n';
    }
}
