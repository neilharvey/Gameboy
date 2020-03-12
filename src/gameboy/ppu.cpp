#include "ppu.h"

Ppu::Ppu(Display display)
{
}

byte Ppu::read(word address)
{
	// http://bgb.bircd.org/pandocs.htm#videodisplay
	switch (address) {
	case 0xFF40:
		return lcdc;
	case 0xFF41:
		return stat;
	case 0xFF42:
		return scroll_y;
	case 0xFF43:
		return scroll_x;
	case 0xFF44:
		return ly;
	case 0xFF45:
		return lyc;
	case 0xFF4A:
		return wy;
	case 0xFF4B:
		return wx;
	}
}

void Ppu::write(word address, byte value)
{
	switch (address) {
	case 0xFF40:
		return lcdc;
	case 0xFF41:
		stat = value;
	case 0xFF42:
		scroll_y = value;
	case 0xFF43:
		scroll_x = value;
	case 0xFF44:
		// ly is read only
	case 0xFF45:
		lyc = value;
	}
}

void Ppu::tick()
{
	// https://youtu.be/HyzD8pNlpwI?t=2727
	// phase order:
	// OAM
	// PIXEL TRANSFER
	// HBLANK

	// VBLANK WHEN LINE 144-154

	switch (mode) {
	case PPUMode::OAM_SEARCH:
		// 20 clocks
	case PPUMode::PIXEL_TRANSFER:
		// 43 clocks
	case PPUMode::HBLANK:
		// 51 clocks
	case PPUMode::VBLANK:
		// 10 lines
	}
}
