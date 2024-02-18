#pragma once

#include <vector>

#include "tile.hpp"
#include "lcd_control.hpp"
#include "../mmu/mmu.hpp"


#define SCROLL_Y 0xFF42
#define SCROLL_X 0xFF43

#define TILE_SIZE_BYTES 16 // consecutive in memory
#define TILE_ROW_SIZE_BYTES 2
#define TILE_PIXEL_SIZE_BITS 2

#define DATA_SELECT_MODE_0 0x8800  // Signed tile id
#define DATA_SELECT_MODE_1 0x8000  // Unsigned tile id

#define VIEWPORT_WIDTH_IN_TILES 20
#define VIEWPORT_HEIGHT_IN_TILES 18

#define VIEWPORT_SCANLINES 144
#define VIEWPORT_COLUMNS 160


typedef std::vector<TileRow> BackgroundRow;
typedef std::vector<BackgroundRow> Background;


class BackgroundBuffer {
    public:
        BackgroundBuffer(LCDControl& lcdControl, MMU& mmu) : lcdControl(lcdControl), mmu(mmu) {};
        Background getViewport();
        BackgroundRow getRow(int row);
        int getTileAddress(int tileId);
        int getTileOffset(int tileId);
        int getTileDataAddress();
        int getTileId(int row, int column);
        TileRow getTileRow(int tileId, int row);

    private:
        LCDControl& lcdControl;
        MMU& mmu;
        int getScrollX();
        int getScrollY();
};