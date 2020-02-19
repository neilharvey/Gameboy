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
	rom(rom)
{
	title = get_title(rom);
	cgb_flag = static_cast<CGBFlag>(rom[0x143]);
	sgb_flag = static_cast<SGBFlag>(rom[0x146]);
	cartridge_type = static_cast<CartridgeType>(rom[0x147]);
	rom_size = static_cast<ROMSize>(rom[0x0148]);
	ram_size = static_cast<RAMSize>(rom[0x0149]);
	destination = static_cast<Destination>(rom[0x14A]);
	rom_version = rom[0x14C];
	header_checksum = rom[0x14D];
	global_checksum = (rom[0x14E] << 8) + rom[0x14F];
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
