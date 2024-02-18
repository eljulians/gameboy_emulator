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

BackgroundRow BackgroundBuffer::getRow(int row) {
}


TileRow BackgroundBuffer::getTileRow(int tileId, int row) {
    auto layoutAddress = lcdControl.getBackgroundTileMapDisplaySelectAddress();
}

int BackgroundBuffer::getTileId(int row, int column) {
    // Within the viewport
    // TODO: wrap screen
    auto xScroll = getScrollX();
    auto yScroll = getScrollY();

    int rowOffset = floor((row + yScroll) / TILE_DIMENSION_PIXELS);
    int columnOffset = floor((column + xScroll) / TILE_DIMENSION_PIXELS);

    return rowOffset * VIEWPORT_WIDTH_IN_TILES + columnOffset;
}

Background BackgroundBuffer::getViewport() {
    // TODO: check if window and background are enabled

    for (int row = 0; row < VIEWPORT_SCANLINES; row++) {
        for (int column = 0; column < VIEWPORT_COLUMNS; column++) {
            auto tileId = getTileId(row, column);
        }
    }
}