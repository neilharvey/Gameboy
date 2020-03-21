#pragma once

#include <vector>

#include "types.h"

class Display {
public:
	Display();
	void set_pixel(int x, int y, int color);
	int get_pixel(int x, int y) const;
private:
	const int SCREEN_WIDTH = 160;
	const int SCREEN_HEIGHT = 144;

	std::vector<int> pixels;
	int pixel_index(int x, int y) const;
};