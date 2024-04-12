#pragma once

#include <stdint.h>
#include <stdint.h>
#include <vector>
#include <map>

#define TILE_WINDOW_PALETTE_ADDRESS 0xFF47

class TilePixelV2;
class MMU;


typedef struct PixelColor {
    short int red;
    short int green;
    short int blue;

    bool operator<=>(const PixelColor&) const = default;
} PixelColor;

static const PixelColor WHITE = {255, 255, 255};
static const PixelColor LIGHT_GRAY = {211, 211, 211};
static const PixelColor DARK_GRAY = {169, 169, 16};
static const PixelColor BLACK = {0, 0, 0};

const std::map<int, PixelColor> ID_COLOR_MAP {
    {0, WHITE},
    {1, LIGHT_GRAY},
    {2, DARK_GRAY},
    {3, BLACK},
};


class Palette {
    public:
        Palette(MMU& mmu) : mmu(mmu) {};
        PixelColor getPixel(uint8_t address, bool first, bool second);

    private:
        MMU& mmu;
};


// TODO: adapt palette implementations to interface 
class BackgroundPalette {
    public:
        BackgroundPalette(MMU& mmu): mmu(mmu) {};
        PixelColor getColor(TilePixelV2 pixel);

    private:
        MMU& mmu;
};

/*
class Pixel {
    public:
        Pixel(bool firstBit, bool secondBit) : firstBit(firstBit), secondBit(secondBit) {};
        bool operator==(const Pixel &other) const {
            return firstBit == other.firstBit && secondBit == other.secondBit;
        }

    private:
        bool firstBit;
        bool secondBit;
};
*/


/*
class PaletteInterface {
    public:
        virtual PixelColor getColor(Pixel pixel) {};
};
*/


/*
class SpritePalette : public PaletteInterface {
    public:
        PixelColor getColor(Pixel pixel);
};
*/