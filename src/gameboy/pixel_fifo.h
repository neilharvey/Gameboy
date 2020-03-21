#pragma once

class PixelFifo {

public:

    PixelFifo();
    void tick();
    int size();
    int dequeue();

private:
    const int MAX_SIZE = 16;
};