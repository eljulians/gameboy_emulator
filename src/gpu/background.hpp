#pragma once

#include <vector>


#define SCROLL_Y 0xFF42
#define SCROLL_X 0xFF43

#define TILE_SIZE_BYTES 16 // consecutive in memory
#define TILE_ROW_SIZE_BYTES 2
#define TILE_PIXEL_SIZE_BITS 2

#define DATA_SELECT_MODE_0 0x9000  // Signed tile id
#define DATA_SELECT_MODE_1 0x8000  // Unsigned tile id

#define BACKGROUND_TILE_LAYOUT_MODE_0_START 0x9800
#define BACKGROUND_TILE_LAYOUT_MODE_0_END 0x9BFF
#define BACKGROUND_TILE_LAYOUT_MODE_1_START 0x9C00
#define BACKGROUND_TILE_LAYOUT_MODE_1_END 0x9FFF

#define BACKGROUND_WIDTH_TILES 32
#define BACKGROUND_HEIGHT_TILES 32

#define VIEWPORT_WIDTH_IN_TILES 20
#define VIEWPORT_HEIGHT_IN_TILES 18

#define VIEWPORT_SCANLINES 144
#define VIEWPORT_COLUMNS 160

class MMU;
class PixelColor;
class LCDControl;
class Scroll;

typedef std::vector<PixelColor> PixelColorVector;

class BackgroundBuffer {
    public:
        BackgroundBuffer(LCDControl& lcdControl, MMU& mmu) : lcdControl(lcdControl), mmu(mmu) {};
        int getTileAddress(int tileId);
        int getTileOffset(int tileId);
        int getTileDataAddress();
        int getTileId(int row, int column);
        PixelColorVector getScanlineViewportRow();
        int getTileIndexInLayout(int row, int column);
        //TilePixelValue getTilePixel(int row, int column, int tileId);
        Scroll getScroll();

    private:
        LCDControl& lcdControl;
        MMU& mmu;
        int getScrollX();
        int getScrollY();
};