#pragma once

#include <stdint.h>
#include <vector>


#define TILE_DIMENSION_PIXELS 8
#define ROWS_IN_TILE 8
#define ROW_SIZE_BYTES 2
#define TILE_SIZE_BYTES ROWS_IN_TILE * ROW_SIZE_BYTES

class MMU;

typedef struct TilePixelV2 {
    bool firstBit;
    bool secondBit;

    bool operator<=>(const TilePixelV2&) const = default;
} TilePixelV2;

// TODO: move somewhere else
typedef struct Scroll {
    int x;
    int y;
} Scroll;




class TileV2 {
    public:
        TileV2(MMU& mmu, int address) : mmu(mmu), address(address) {};
        TilePixelV2 getValue(int row, int column, Scroll scroll);

    private:
        MMU& mmu;
        int address;
};