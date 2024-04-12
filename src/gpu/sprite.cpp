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

/*
void SpriteClient::fetchSprites() {
    uint8_t attributesAddress = ATTRIBUTE_TABLE_ADDRESS_START;

    for (int i = 0; i < TOTAL_SPRITE_COUNT; i++) { 
        uint8_t y = mmu.read_8bit(attributesAddress);
        uint8_t x = mmu.read_8bit(attributesAddress+1);
        uint8_t patternNumber = mmu.read_8bit(attributesAddress+2);
        uint8_t attributes = mmu.read_8bit(attributesAddress+3);

        Sprite sprite = Sprite(y, x, patternNumber, attributes);

        attributesAddress += ATTRIBUTE_SIZE_BYTES;
    }
}
*/

SpriteVector SpriteClient::getSprites(uint8_t y) {
    uint16_t attributesAddress = ATTRIBUTE_TABLE_ADDRESS_START;
    SpriteVector sprites;
    sprites.reserve(TOTAL_SPRITE_COUNT);


    for (int i = 0; i < TOTAL_SPRITE_COUNT; i++) { 
        uint8_t y = mmu.read_8bit(attributesAddress);
        uint8_t x = mmu.read_8bit(attributesAddress+1);
        uint8_t patternNumber = mmu.read_8bit(attributesAddress+2);
        uint8_t attributes = mmu.read_8bit(attributesAddress+3);
        attributesAddress += ATTRIBUTE_SIZE_BYTES;

        if (i == 0) {
            spdlog::debug(y);
            spdlog::debug(x);
            spdlog::debug(patternNumber);
            spdlog::debug(attributes);
            spdlog::debug("=========");
        }

        Sprite sprite = Sprite(y-16, x-8, patternNumber, attributes);

        if (y == 0x80){

        }


        //if (sprite.y == y) {
            sprites.push_back(sprite);
       // }
    }

    return sprites;
}