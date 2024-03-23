#include <stdint.h>
#include <vector>

#include "background.hpp"
#include "tile.hpp"
#include "../mmu/mmu.hpp"


TilePixelV2 TileV2::getValue(int row, int column, Scroll scroll) {
    /*
    Row and column are absolute wrt the screen rather than relative wrt the tile,
    i.e. ranges are [0, 160], [0, 144].
    */
    //int rowOffset = ((row + scroll.y) % 8) * ROW_SIZE_BYTES;
    //int columnOffset = 7 - ((column + scroll.x) % 8);
    int rowOffset = (row  % 8) * ROW_SIZE_BYTES;
    int columnOffset = 7 - (column % 8);

    uint8_t firstByte = mmu.read_8bit(address + rowOffset);
    uint8_t secondByte = mmu.read_8bit(address + rowOffset + 1);

    bool firstBit = (firstByte >> columnOffset) & 1;
    bool secondBit = (secondByte >> columnOffset) & 1;

    return TilePixelV2{firstBit, secondBit};
}