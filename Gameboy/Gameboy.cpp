#include <iostream>
#include "Cpu.h"
#include "Mmu.h"

int main()
{
    try
    {
        Mmu mmu;
        Cpu cpu(mmu);
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
