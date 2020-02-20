#include "cartridge.h"

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

Cartridge Cartridge::load(std::string romPath)
{
	using std::ifstream;
	using std::ios;

	ifstream stream(romPath, ios::binary | ios::ate);

	if (!stream.is_open()) {
		throw std::runtime_error("Could not open " + romPath);
	}

	auto size = stream.tellg();
	std::vector<char> buffer(size);

	stream.seekg(0, ios::beg);
	stream.read(&buffer[0], size);
	stream.close();

	auto rom = std::vector<byte>(buffer.begin(), buffer.end());
	Cartridge cartridge(rom);

	return cartridge;
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
