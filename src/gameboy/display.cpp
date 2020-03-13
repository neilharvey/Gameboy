#include "display.h"

void Display::Display() {
    pixels(WIDTH * HEIGHT, 0);
}

void Display::set_pixel(int x, int y, int color) {
     pixels[(y * WIDTH) + x] = color;
}

int Display::get_pixel(int x, int y) const
{
    return pixels[(y * WIDTH) + x];
}
