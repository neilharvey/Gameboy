#pragma once

#include "pixel_fifo.h"

class Fetcher {
public:
    Fetcher(PixelFifo& fifo);
    void tick();
 private:
     PixelFifo& fifo;
};