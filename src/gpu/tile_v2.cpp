#include <stdint.h>
#include <vector>

#include "tile_v2.hpp"


TilePixelV2 TileV2::getValue(int row, int column, Scroll scroll) {
    int rowOffset = (row + scroll.y) * ROW_SIZE_BYTES;
    int columnOffset = 7 - ((column + scroll.x) % 8);
    int mask = 1 << columnOffset;

    uint8_t firstByte = mmu.read_8bit(address + rowOffset);
    uint8_t secondByte = mmu.read_8bit(address + rowOffset + 1);

    bool firstBit = (firstByte >> columnOffset) & 1;
    bool secondBit = (secondByte >> columnOffset) & 1;

    return TilePixelV2{firstBit, secondBit};
}