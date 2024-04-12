#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include "spdlog/spdlog.h"

#include <stdint.h>
#include "gpu.hpp"
#include "lcd_control.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "color.hpp"
#include "sprite.hpp"
#include "../mmu/mmu.hpp"



#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 140


void GPU::init_sdl() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void GPU::update(uint8_t cycles) {
    int currentScanline = lcdControl.getCurrentScanline();

    spdlog::debug("LCDC: 0x{0:x}", lcdControl.getLCDControlValue());
    spdlog::debug("STAT: 0x{0:x}", lcdControl.getStatus());
    SpriteVector sprites;

    if (currentScanline != lastDrawnScanline) {
        lastDrawnScanline = currentScanline;
        PixelColorVector pixelVector = backgroundBuffer.getScanlineViewportRow();

        for (int i = 0; i < pixelVector.size(); i++) {
            PixelColor pixel = pixelVector.at(i);
            SDL_SetRenderDrawColor(renderer, pixel.red, pixel.green, pixel.blue, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, currentScanline);
        }

        if (lcdControl.getSpriteDisplay()) {
            sprites = spriteClient.getSprites(currentScanline);
            for (auto& sprite : sprites) {

                if (sprite.patternNumber == 0x58) {

                }

                if (currentScanline - sprite.y >= 0 && currentScanline - sprite.y <= 8) {
                    auto spriteLine = currentScanline - sprite.y;
                    auto patternNumber = sprite.patternNumber;

                    // Each whole sprite 16 bytes
                    // Each sprite line 2 bytes
                    auto patternAddress = 0x8000 + patternNumber * 16 + spriteLine * 2;
                    auto first = mmu.read_8bit(patternAddress);
                    auto second = mmu.read_8bit(patternAddress+1);
                    auto paletteAddress = sprite.attributes.getPaletteAddress();
                    auto palette = mmu.read_8bit(paletteAddress);

                    if (sprite.y == 0x80) {

                    }
                    int k = 0;
                    for (int j = 7; j >= 0; j--) {
                        auto mask = (1 << (j-spriteLine));
                        auto firstBit = (first >> j) & 1;
                        auto secondBit = (second >> j) & 1;
                        auto colorCode = (firstBit << 1) + secondBit;

                        auto darkest = (palette & 0b11000000) >> 6;
                        auto bit_lighter = (palette & 0b00110000 >> 4);
                        auto even_lighter = (palette & 0b00001100 >> 2);
                        auto lightest = palette & 0b00000011;

                        if (colorCode == darkest) {
                            SDL_SetRenderDrawColor(
                                renderer,
                                0,
                                0,
                                0,
                                SDL_ALPHA_OPAQUE
                            );
                            
                        } else if (colorCode == bit_lighter) {
                            SDL_SetRenderDrawColor(
                                renderer,
                                169,
                                169,
                                169,
                                SDL_ALPHA_OPAQUE
                            );

                        } else if (colorCode == even_lighter) {
                            SDL_SetRenderDrawColor(
                                renderer,
                                211,
                                211,
                                211,
                                SDL_ALPHA_OPAQUE
                            );
                        } else {
                            // White is transparent for sprites
                            SDL_SetRenderDrawColor(
                                renderer,
                                255,
                                255,
                                255,
                                SDL_ALPHA_OPAQUE
                            );
                        }

                        SDL_RenderDrawPoint(renderer, sprite.x+k, currentScanline);
                        k++;
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    if (lcdControl.getSpriteDisplay()) {
        //spriteClient.fetchSprites();
        //sprites = spriteClient.getSprites(currentScanline);
    }

    lcdControl.update(cycles);
}