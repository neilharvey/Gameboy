#pragma once

#include "types.h"

class Display {
public:
	void set_pixel(byte x, byte y, byte color);
	void refresh();
};