#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "types.h"

enum class CartridgeType {

	ROM_ONLY = 0x00,                 
	MBC1 = 0x01,                     
	MBC1_RAM = 0x02,                 
	MBC1_RAM_BATTERY = 0x03,        
	MBC2 = 0x05,                     
	MBC2_BATTERY = 0x06,            
	ROM_RAM = 0x08,                  
	ROM_RAM_BATTERY = 0x09,         
	MMM01 = 0x0B,                    
	MMM01_RAM = 0x0C,                
	MMM01_RAM_BATTERY = 0x0D,        
	MBC3_TIMER_BATTERY = 0x0F,       
	MBC3_TIMER_RAM_BATTERY = 0x10,   
	MBC3 = 0x11,                     
	MBC3_RAM = 0x12,
	MBC3_RAM_BATTERY = 0x13,
	MBC4 = 0x15,
	MBC4_RAM = 0x16,
	MBC4_RAM_BATTERY = 0x17,
	MBC5 = 0x19,
	MBC5_RAM = 0x1A,
	MBC5_RAM_BATTERY = 0x1B,
	MBC5_RUMBLE = 0x1C,
	MBC5_RUMBLE_RAM = 0x1D,
	MBC5_RUMBLE_RAM_BATTERY = 0x1E,
	POCKET_CAMERA = 0xFC,
	BANDAI_TAMA5 = 0xFD,
	HUC3 = 0xFE,
	HUC1_RAM_BATTERY = 0xFF
};

enum class ROMSize {
	ROM_32KB = 0x00,
	ROM_64KB = 0x01,
	ROM_128KB = 0x02,
	ROM_256KB = 0x03,
	ROM_512KB = 0x04,
	ROM_1MB = 0x05,
	ROM_2MB = 0x06,
	ROM_4MB = 0x07,
	ROM_1P1MB = 0x52,
	ROM_1P2MB = 0x53,
	ROM_1P5MB = 0x54
};

enum class RAMSize {
	NONE = 0x00,
	RAM_2KB = 0x01,
	RAM_8KB = 0x02,
	RAM_32KB = 0x03
};

enum class CGBFlag {
	GB_AND_GBC = 0x80,
	GBC_ONLY = 0xC0
};

enum class SGBFlag {
	NORMAL = 0x00,
	SGB = 0x03
};

enum class Destination {
	JAPANESE = 0x00,
	NON_JAPANESE = 0x01
};

class Cartridge {
public:

	// http://bgb.bircd.org/pandocs.htm#thecartridgeheader
	std::string title; 

	CGBFlag cgb_flag; 
	SGBFlag sgb_flag; 
	CartridgeType cartridge_type;
	ROMSize rom_size;
	RAMSize ram_size;
	Destination destination; 

	byte rom_version; 
	byte header_checksum; 
	word global_checksum;

	static Cartridge load(std::string romPath);
	Cartridge(std::vector<byte> rom);

	byte read(word address);
	void write(word address, byte value);

private:
	std::vector<byte> rom;
	std::string get_title(std::vector<byte> rom);
};