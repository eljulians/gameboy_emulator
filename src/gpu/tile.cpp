#include "tile.hpp"


TilePixelVector TileRow::createPixels() {
    TilePixelVector tilePixelVector;
    tilePixelVector.reserve(PIXELS_IN_ROW);
    uint8_t mask = 0x80;
    bool firstBit, secondBit;

    for (int i = 0; i < PIXELS_IN_ROW; i++) {
        firstBit = firstByte & mask;
        secondBit = secondByte & mask;
        mask >>= 1;

        tilePixelVector.push_back(TilePixel(firstBit, secondBit));
    }

    return tilePixelVector;
}