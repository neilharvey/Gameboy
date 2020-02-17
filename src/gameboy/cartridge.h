#pragma once
#include <string>
#include <memory>
#include <vector>
#include "types.h"

enum class CartridgeType {
	NONE,
	MBC1,
	MBC2,
	MBC3,
	HUC1,
};

enum class CGBFlag {
	BACKWARDS_COMPATIBLE,
	GBC_ONLY
};

class Cartridge {
public:

	// http://bgb.bircd.org/pandocs.htm#thecartridgeheader
	// entry point // 0100-0103
	// ninendo logo // 0104-0133
	std::string title; // 0134-0143
	//std::string manufacturer_code; // 013F-0142
	CGBFlag cgb_flag; // 0143
	//word new_licensee_code; // 0144-0145
	//byte sgb_flag; // 0146
	CartridgeType cartridge_type; // 0147 -> mbc_type
	//byte rom_size; // 0148
	//byte ram_size; // 0148
	//byte destination_code; // 014Al
	//byte old_licensee_code; // 014B
	//byte rom_version; // 014C
	//byte header_checksum; // 014D
	//word global_checksum;

	//static std::unique_ptr<Cartridge> load(const char* romPath);
	Cartridge(std::vector<byte> rom);

	byte read(word address);
	void write(word address, byte value);

private:
	std::vector<byte> rom;
	std::string get_title(std::vector<byte> rom);
};