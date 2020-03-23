#pragma once

#include "pixel_fifo.h"

class Fetcher {
public:

    enum class FetcherState {
        READ_TILE_ID,
        READ_DATA_0,
        READ_DATA_1,
        PUSH
    };


    Fetcher(PixelFifo& fifo);
    void tick();
 private:     
     PixelFifo& fifo;
     FetcherState state;
};