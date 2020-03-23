#include "fetcher.h"
#include "fetcher.h"

Fetcher::Fetcher(PixelFifo& fifo)
    : fifo(fifo)
{
    state = FetcherState::READ_TILE_ID;
}

void Fetcher::tick()
{
    switch (state) {
    case FetcherState::READ_TILE_ID:
        break;
    case FetcherState::READ_DATA_0:
        break;
    case FetcherState::READ_DATA_1:
        break;
    case FetcherState::PUSH:
        break;
    }
}