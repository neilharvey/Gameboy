#pragma once

#include "types.h"

class Display {
public:
	virtual void set_pixel(byte x, byte y, byte color);
	virtual void refresh();
};