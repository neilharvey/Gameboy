#include "cartridge.h"

//static std::unique_ptr<Cartridge> load(const char* romPath)
//{
//    using std::ifstream;
//    using std::ios;
//    using std::streampos;
//    using std::vector;
//
//    ifstream file(romPath, ios::in | ios::binary | ios::ate);
//    streampos size = file.tellg();
//    char* bytes = new char[size];
//
//    file.seekg(0, ios::beg);
//    file.read(bytes, size);
//    file.close();
//
//    byte* rom = bytes;
//    return Cartridge(bytes, size);
//}

Cartridge::Cartridge(std::vector<byte> rom) :
	cartridge_type(CartridgeType::NONE),
	rom(rom)
{
	title = get_title(rom);

}

byte Cartridge::read(word address)
{
	return rom[address];
}

void Cartridge::write(word address, byte value)
{
	rom[address] = value;
}

std::string Cartridge::get_title(std::vector<byte> rom)
{
	title = "";
	for (byte i = 0; i < 15; i++) {
		word address = 0x134 + i;
		char character = rom[address];
		if (character == 0) {
			break;
		}

		title += character;
	}

	return title;
}

