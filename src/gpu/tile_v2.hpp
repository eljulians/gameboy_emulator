#pragma once

#include <stdint.h>
#include <vector>

#include "../mmu/mmu.hpp"
#include "background.hpp"

#define ROWS_IN_TILE 8
#define ROW_SIZE_BYTES 2
#define TILE_SIZE_BYTES ROWS_IN_TILE * ROW_SIZE_BYTES


typedef struct TilePixelV2 {
    bool firstBit;
    bool secondBit;

    bool operator<=>(const TilePixelV2&) const = default;
} TilePixelV2;



class TileV2 {
    public:
        TileV2(MMU& mmu, int address) : mmu(mmu), address(address) {};
        TilePixelV2 getValue(int row, int column, Scroll scroll);

    private:
        MMU& mmu;
        int address;
};