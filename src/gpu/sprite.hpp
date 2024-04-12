#pragma once

#include <stdint.h>
#include <map>
#include <vector>

#define ATTRIBUTE_TABLE_ADDRESS_START 0xFE00
#define ATTRIBUTE_SIZE_BYTES 4
#define TOTAL_SPRITE_COUNT 40

#define SPRITE_TILE_PATTERN_ADDRESS 0x8000
#define SPRITE_TILE_SIZE_BYTES 16
#define SPRITE_LINE_SIZE_BYTES 2

class LCDControl;
class MMU;
class PixelColor;
class Palette;


class SpriteAttributes {
    public:
        SpriteAttributes() {};
        SpriteAttributes(uint8_t attributes) : attributes(attributes) {};

        bool isBehindBackground();
        bool xFlip();
        bool yFlip();
        uint16_t getPaletteAddress();

    private:
        uint8_t attributes;
};

class Sprite {
    public:
        Sprite(MMU& mmu, uint8_t y_, uint8_t x_, uint8_t patternNumber_, uint8_t attributes_) : mmu(mmu) {
            y = y_;
            x = x_;
            patternNumber = patternNumber_;
            attributes = SpriteAttributes(attributes_);
        };
        uint16_t getPatternAddress(int relativeY);
        PixelColor getPixel(int relativeX, int relativeY);

        uint8_t x;
        uint8_t y;
        uint8_t patternNumber;
        SpriteAttributes attributes;

    private:
        MMU& mmu;
};

typedef std::vector<Sprite> SpriteVector;


class SpriteClient {
    public:
        SpriteClient(LCDControl& lcdControl, MMU& mmu) : lcdControl(lcdControl), mmu(mmu) {};

        // Fetch sprites for the cycle, store them, and then they will be returned
        // based on priority
        void fetchSprites();
        SpriteVector getSprites(uint8_t y);
        /*
        SpriteVector getHighPrioritySprites();
        SpriteVector getLowPrioritySprites();
        */

    private:
        MMU& mmu;
        LCDControl& lcdControl;
        std::map<bool, SpriteVector> prioritySpriteMap;
};