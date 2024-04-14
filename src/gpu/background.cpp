#include <cmath>

#include "spdlog/spdlog.h"

#include <iostream>
#include <stdio.h>
#include "background.hpp"
#include "tile.hpp"
#include "lcd_control.hpp"
#include "../mmu/mmu.hpp"
#include "tile.hpp"
#include "color.hpp"


Scroll BackgroundBuffer::getScroll() {
    return Scroll{
        mmu.read_8bit(SCROLL_X),
        mmu.read_8bit(SCROLL_Y),
    };
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

    return static_cast<int8_t>(tileId);
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
    Scroll scroll = getScroll();


    int scrolledRow = row + scroll.y;
    int scrolledX = column + scroll.x;

    if (scrolledRow >=256) {
        scrolledRow = 256 - scrolledRow;
    }

    //if (scrolledX >= 256) {
    //    scrolledX = 256 - scrolledX;
    //}

    int rowOffset = floor(scrolledRow / TILE_DIMENSION_PIXELS);
    int columnOffset = floor(scrolledX / TILE_DIMENSION_PIXELS);

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


PixelColorVector BackgroundBuffer::getScanlineViewportRow() {
    // TODO: check if window and background are enabled, deal with window etc
    auto currentScanline = lcdControl._cachedCurrentScanline;
    Scroll scroll = getScroll();

    // TODO: class attribute
    BackgroundPalette palette = BackgroundPalette(mmu);
    PixelColorVector pixels;
    pixels.reserve(VIEWPORT_COLUMNS);

    for (int column = 0; column < VIEWPORT_COLUMNS; column++) {
        auto tileId = getTileId(currentScanline, column);

        auto tileAddress = getTileAddress(tileId);
        TileV2 tile = TileV2(mmu, tileAddress);
        TilePixelV2 pixel = tile.getValue(currentScanline, column, scroll);
        PixelColor pixelColor = palette.getColor(pixel);
        pixels.push_back(pixelColor);
    }

    return pixels;
}