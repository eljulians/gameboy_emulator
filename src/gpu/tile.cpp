#include "tile.hpp"


int TilePixel::getValue() {
    return firstBit << 1 | secondBit;
}

TilePixelVector TileRow::createPixels() {
    uint8_t mask = 0x80;
    bool firstBit, secondBit;

    for (int i = 0; i < PIXELS_IN_ROW; i++) {
        firstBit = firstByte & mask;
        secondBit = secondByte & mask;
        mask >>= 1;

        pixels.push_back(TilePixel(firstBit, secondBit));
    }

    return pixels;
}

TileRowVector Tile::createRows() {
    for (int i = 0; i < bytes.size(); i+=2) {
        auto firstByte = bytes[i];
        auto secondByte = bytes[i+1];

        TileRow tileRow(firstByte, secondByte);
        tileRow.createPixels();
        rows.push_back(tileRow);
    }
        
    return rows;
}