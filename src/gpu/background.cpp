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

    return dataAddress + tileOffset * TILE_SIZE;
}

BackgroundRow BackgroundBuffer::getRow(int row) {

}


Background BackgroundBuffer::getViewport() {
    
}