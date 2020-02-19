#include "Main.h"

int main()
{
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

    std::cout << cartridge.title << '\n';
}
