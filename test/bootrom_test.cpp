//#include <cpu.h>
//
//#include "lib/catch/catch.hpp"
//
//TEST_CASE("Boot ROM can be run", "[CPU]") {
//
//	std::string romPath = "../../../../test/resources/blargg/cpu_instrs.gb";
//	auto cartridge = Cartridge::load(romPath);
//
//	Display display;
//	Gpu gpu (display);
//	std::unique_ptr<Mmu> mmu = std::make_unique<Mmu>(gpu, cartridge);
//	Cpu cpu(*mmu);
//
//	SECTION("Stack is initialised") {
//
//		cpu.tick(); // 0x0000 – LD SP, $0xFFFE
//
//		REQUIRE(cpu.sp == 0xFFFE);
//	}
//
//	SECTION("Video RAM is initialised") {
//
//		// 0x0003 – XOR A
//		// 0x0004 – LD HL, $0x9FFF
//		// 0x0007 – LD (HL-), A
//		// 0x0008 – BIT 7, H
//		// 0x000A – JRNZ . + 0xfb
//		// 0x000C – LD HL, $0xFF26
//
//		cpu.pc = 0x0003;
//		while (cpu.sp < 0x000C) {
//			cpu.tick();
//		}
//
//		int checksum = 0;
//		for (word address = 0x8000; address <= 0x9FFF; address++) {
//			checksum += mmu->read(address);
//		}
//
//		REQUIRE(checksum == 0);
//	}
//
//	SECTION("Audio is initialised") {
//
//		cpu.pc = 0x000C;
//		
//		cpu.tick(); // 0x000C – LD HL, $0xFF26 # load 0xFF26 to HL
//		cpu.tick(); // 0x000F – LD C, $0x11 # load 0x11 to C
//		cpu.tick(); // 0x0011 – LD A, $0x80 # load 0x80 to A
//		cpu.tick(); // 0x0013 – LD (HL-), A # load A to address pointed to by HL and Dec HL
//		cpu.tick(); // 0x0014 – LD ($0xFF00 + C), A # load A to address 0xFF00 + C (0xFF11)
//		cpu.tick(); // 0x0015 – INC C # increment C register
//		cpu.tick(); // 0x0016 – LD A, $0xF3 # load 0xF3 to A
//		cpu.tick(); // 0x0018 – LD ($0xFF00 + C), A # load A to address 0xFF00 + C(0xFF12)
//		cpu.tick(); // 0x0019 – LD (HL-), A # load A to address pointed to by HL and Dec HL
//		cpu.tick(); // 0x001A – LD A, $0x77 # load 0x77 to A
//		cpu.tick(); // 0x001C – LD (HL), A # load A to address pointed to by HL
//		
//		REQUIRE(mmu->read(0xFF11) == 0x80);
//		REQUIRE(mmu->read(0xFF26) == 0x80);
//		REQUIRE(mmu->read(0xFF12) == 0xF3);
//		REQUIRE(mmu->read(0xFF25) == 0xF3);
//		REQUIRE(mmu->read(0xFF24) == 0x77);
//	}
//
//	SECTION("Background palette is initialised") {
//
//		cpu.pc = 0x001D;
//
//		cpu.tick(); // 0x001D – LD A, $0xFC # A represents the color number’s mappings
//		cpu.tick(); // 0x001F – LD($0xFF00 + $0x47), A # initialize the palette
//
//		REQUIRE(mmu->read(0xFF47) == 0xFC);
//	}
//}