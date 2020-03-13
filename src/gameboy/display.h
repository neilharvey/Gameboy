#pragma once

#include <vector>

#include "types.h"

class Display {
public:

	const int WIDTH = 160;
	const int HEIGHT = 144;

	void set_pixel(int x, int y, int color);
	int get_pixel(int x, int y) const;
private:
	std::vector<int> pixels;
};