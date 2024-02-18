#include <cmath>

#include "background.hpp"
#include "tile.hpp"
#include "lcd_control.hpp"
#include "../mmu/mmu.hpp"


int BackgroundBuffer::getScrollX() {
    return mmu.read_8bit(SCROLL_X);
}


int BackgroundBuffer::getScrollY() {
    return mmu.read_8bit(SCROLL_Y);
}

int BackgroundBuffer::getTileDataAddress() {
    BackgroundAndWindowTileDataSelect select = lcdControl.getBackgroundAndWindowTileDataSelect();

    if (select == BackgroundAndWindowTileDataSelect::FIRST_SIGNED) {
        return DATA_SELECT_MODE_0;
    } else {
        return DATA_SELECT_MODE_1;
    }
}

int BackgroundBuffer::getTileOffset(int tileId) {
    // If select mode is 1, id is an unsigned byte ranging from -128 to 127 
    BackgroundAndWindowTileDataSelect select = lcdControl.getBackgroundAndWindowTileDataSelect();

    if (select == BackgroundAndWindowTileDataSelect::SECOND_UNSIGNED) {
        return tileId;
    }

    if (tileId >= 128) {
        return tileId - 128;
    }
    return tileId + 128;
}

int BackgroundBuffer::getTileAddress(int tileId) {
    auto dataAddress = getTileDataAddress();
    auto tileOffset = getTileOffset(tileId);

    return dataAddress + tileOffset * TILE_SIZE_BYTES;
}


int BackgroundBuffer::getTileIndexInLayout(int row, int column) {
    /*
    What's the offset for the layout address ($9800/$9C00, depending on bit 3
    of LCD control) for a given screen coordinate?
    */
    auto xScroll = getScrollX();
    auto yScroll = getScrollY();

    int rowOffset = floor((row + yScroll) / TILE_DIMENSION_PIXELS);
    int columnOffset = floor((column + xScroll) / TILE_DIMENSION_PIXELS);

    return rowOffset * BACKGROUND_WIDTH_TILES + columnOffset;
}

int BackgroundBuffer::getTileId(int row, int column) {
    /*
    Whether the ID it's signed or unsigned will be determined later when getting the
    tile adress
    */
    auto tileIndex = getTileIndexInLayout(row, column);
    auto layoutAddress = lcdControl.getBackgroundLayoutAddress();

    return mmu.read_8bit(layoutAddress + tileIndex);
}

TileRow BackgroundBuffer::getCurrentScanlineTileRow() {
    auto currentScanline = lcdControl.getCurrentScanline();

    for (int column = 0; column < VIEWPORT_COLUMNS; column++) {

        auto tileId = getTileId(currentScanline, column);
    }
}


BackgroundRow BackgroundBuffer::getScanlineViewportRow() {
    // TODO: check if window and background are enabled, deal with window etc
    auto currentScanline = lcdControl.getCurrentScanline();
    for (int column = 0; column < VIEWPORT_COLUMNS; column++) {
        auto tileId = getTileId(currentScanline, column);
    }
}