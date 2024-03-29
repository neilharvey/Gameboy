#pragma once

#include "display.h"
#include "fetcher.h"
#include "pixel_fifo.h"
#include "types.h"

// https://gbdev.gg8.se/wiki/articles/Video_Display

class Ppu {
public:

	enum class PPUMode {
		HBLANK,
		VBLANK,
		OAM_SEARCH,
		PIXEL_TRANSFER
	};

	Ppu(std::vector<byte>& vram, Display& display);

	byte read(word address) const;
	void write(word address, byte value);
	void tick();

private:

	const int TICKS_PER_OAM_SEARCH = 20 * 4;
	const int TICKS_PER_LINE = 456;

	const int PIXELS_PER_LINE = 160;
	const int VBLANK_START_LINE = 144;
	const int VBLANK_END_LINE = 154;

	Display& display;
	PPUMode mode;
	Fetcher fetcher;
	PixelFifo fifo;

	std::vector<byte>& vram;

	// LCD Control
	// Bit 7 - LCD Display Enable(0 = Off, 1 = On)
	// Bit 6 - Window Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
	// Bit 5 - Window Display Enable(0 = Off, 1 = On)
	// Bit 4 - BG & Window Tile Data Select(0 = 8800 - 97FF, 1 = 8000 - 8FFF)
	// Bit 3 - BG Tile Map Display Select(0 = 9800 - 9BFF, 1 = 9C00 - 9FFF)
	// Bit 2 - OBJ(Sprite) Size(0 = 8x8, 1 = 8x16)
	// Bit 1 - OBJ(Sprite) Display Enable(0 = Off, 1 = On)
	// Bit 0 - BG / Window Display / Priority(0 = Off, 1 = On)
	byte lcdc;

	// Bit 6 - LYC = LY Coincidence Interrupt(1 = Enable) (Read / Write)
	// Bit 5 - Mode 2 OAM Interrupt(1 = Enable) (Read / Write)
	// Bit 4 - Mode 1 V - Blank Interrupt(1 = Enable) (Read / Write)
	// Bit 3 - Mode 0 H - Blank Interrupt(1 = Enable) (Read / Write)
	// Bit 2 - Coincidence Flag(0:LYC<>LY, 1 : LYC = LY) (Read Only)
	// Bit 1 - 0 - Mode Flag(Mode 0 - 3, see below) (Read Only)
	// 	0 : During H - Blank
	// 	1 : During V - Blank
	// 	2 : During Searching OAM - RAM
	// 	3 : During Transfering Data to LCD Driver
	byte stat;

	// Range 0-255
	byte scroll_x;
	byte scroll_y;

	byte ly;
	byte lyc;

	byte wy;
	byte wx;

	int ticks;
	int pixels;

	void oam_search();
	void pixel_transfer();
	void hblank();
	void vblank();
};