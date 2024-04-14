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
    // TODO: handle X and Y flips
    auto patternAddress = getPatternAddress(relativeY);
    auto first = mmu.read_8bit(patternAddress);
    auto second = mmu.read_8bit(patternAddress+1);
    auto paletteAddress = attributes.getPaletteAddress();
    auto palette = mmu.read_8bit(paletteAddress);

    auto firstBit = (first >> relativeX) & 1;
    auto secondBit = (second >> relativeX) & 1;
    auto colorCode = (firstBit << 1) + secondBit;

    return ID_COLOR_MAP.at(colorCode);
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

        Sprite sprite = Sprite(mmu, y-16, x-8, patternNumber, attributes);
        sprites.push_back(sprite);
    }

    return sprites;
}