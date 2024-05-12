#include "sprite.hpp"
#include "color.hpp"
#include "../mmu/mmu.hpp"
#include "../common/bit_operations.hpp"
#include <vector>
#include "spdlog/spdlog.h"


bool SpriteAttributes::isBehindBackground() {
    return testBit(attributes, 7);
}

bool SpriteAttributes::yFlip() {
    return testBit(attributes, 6);
}

bool SpriteAttributes::xFlip() {
    return testBit(attributes, 5);
}

uint16_t SpriteAttributes::getPaletteAddress() {
    uint16_t address = testBit(attributes, 4) ? 0xFF49 : 0xFF48;

    return address;
}

uint16_t Sprite::getPatternAddress(int relativeY) {
    return SPRITE_TILE_PATTERN_ADDRESS + patternNumber * SPRITE_TILE_SIZE_BYTES + relativeY * SPRITE_LINE_SIZE_BYTES;
}

PixelColor Sprite::getPixel(int relativeX, int relativeY) {
    if (attributes.xFlip()) {
        // Read sprite data backwards; e.g. 7 -> 0, 6 -> 1, etc
        relativeX -= 7;
        relativeX *= -1;
    }
    if (attributes.yFlip()) {
        relativeY -= 7;
        relativeY *= -1;
    }


    auto patternAddress = getPatternAddress(relativeY);
    auto first = mmu.read_8bit(patternAddress);
    auto second = mmu.read_8bit(patternAddress+1);
    auto paletteAddress = attributes.getPaletteAddress();
    auto palette = mmu.read_8bit(paletteAddress);

    auto firstBit = (first >> relativeX) & 1;
    auto secondBit = (second >> relativeX) & 1;
    auto colorCode = (firstBit << 1) + secondBit;

    int shift = colorCode * 2;  // 2 bits

    if (patternNumber == 4 && relativeX == 0) {
        // nose pattern number is 4
        // it's being drawn with the same color
        //spdlog::error("0x{:0X}", paletteAddress);
    }


    return ID_COLOR_MAP.at((palette >> shift) & 0b11);

    /*
    uint8_t pattern = mmu.read_8bit(TILE_WINDOW_PALETTE_ADDRESS);
    int code = (pixel.firstBit << 1) + pixel.secondBit;
    int shift = code * 2;

    return ID_COLOR_MAP.at((pattern >> shift) & 0b11);
    */

    //return ID_COLOR_MAP.at(colorCode);
}

SpriteVector SpriteClient::getSprites(uint8_t y) {
    uint16_t attributesAddress = ATTRIBUTE_TABLE_ADDRESS_START;
    SpriteVector sprites;

    int enabledSpriteCount = 0;


    for (int i = 0; i < TOTAL_SPRITE_COUNT; i++) { 
        uint8_t y = mmu.read_8bit(attributesAddress);
        uint8_t x = mmu.read_8bit(attributesAddress+1);
        uint8_t patternNumber = mmu.read_8bit(attributesAddress+2);
        uint8_t attributes = mmu.read_8bit(attributesAddress+3);
        attributesAddress += ATTRIBUTE_SIZE_BYTES;

        Sprite sprite = Sprite(mmu, lcdControl, y-16, x-8, patternNumber, attributes);
        sprites.push_back(sprite);
    }

    return sprites;
}