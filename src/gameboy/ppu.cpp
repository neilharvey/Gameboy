#include "ppu.h"
#include "ppu.h"
#include "ppu.h"
#include "ppu.h"
#include "ppu.h"

Ppu::Ppu(std::vector<byte>& vram, Display& display) :
	vram(vram),
	display(display)
{
	mode = PPUMode::OAM_SEARCH;
	ticks = 0;
}

byte Ppu::read(word address) const
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

	ticks++;

	switch (mode) {
	case PPUMode::OAM_SEARCH:
		oam_search();
		break;
	case PPUMode::PIXEL_TRANSFER:
		pixel_transfer();
		break;
	case PPUMode::HBLANK:
		hblank();
		break;
	case PPUMode::VBLANK:
		vblank();
		break;
	}
}

void Ppu::oam_search()
{
	// https://youtu.be/HyzD8pNlpwI?t=2753
	// determine 10 visible sprites to display

	if (ticks == TICKS_PER_OAM_SEARCH) {
		mode = PPUMode::PIXEL_TRANSFER;
	}
}

void Ppu::pixel_transfer()
{
	// https://youtu.be/HyzD8pNlpwI?t=2957

	fetcher.tick();

	if (fifo.size() > 8) {
		display.set_pixel(pixels++, line, fifo.dequeue());
	
		if (pixels == PIXELS_PER_LINE) {
			mode = PPUMode::HBLANK;
		}	
	}
}

void Ppu::hblank()
{	
	if (ticks == TICKS_PER_LINE) {
		ticks = 0;
		if (++ly == VBLANK_START_LINE) { 
			// render the image at this point?
			mode = PPUMode::VBLANK;
		} else {
			mode = PPUMode::OAM_SEARCH;
		}
	}
}

void Ppu::vblank()
{
	if (ticks == TICKS_PER_LINE) {
		ticks = 0;
		if (++ly == VBLANK_END_LINE) {
			mode = PPUMode::OAM_SEARCH;
			line = 0;
		}
	}
}
