#include "display.h"

Display::Display() :
    pixels(SCREEN_WIDTH * SCREEN_HEIGHT, 0)
{
}

void Display::set_pixel(int x, int y, int color) {
     pixels[pixel_index(x, y)] = color;
}

int Display::get_pixel(int x, int y) const
{
    return pixels[pixel_index(x,y)];
}

int Display::pixel_index(int x, int y) const
{
    return x + (y * SCREEN_WIDTH);
}
