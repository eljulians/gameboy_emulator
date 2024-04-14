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

    //spdlog::debug("LCDC: 0x{0:x}", lcdControl.getLCDControlValue());
    //spdlog::debug("STAT: 0x{0:x}", lcdControl.getStatus());
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
            // TODO handle 8x16 sprites
            sprites = spriteClient.getSprites(currentScanline);
            for (auto& sprite : sprites) {

                if (currentScanline - sprite.y >= 0 && currentScanline - sprite.y <= 8) {
                    auto spriteLine = currentScanline - sprite.y;

                    // TODO refactor this shit
                    int k = 0;
                    for (int j = 7; j >= 0; j--) {
                        auto pixel = sprite.getPixel(j, spriteLine);
                        SDL_SetRenderDrawColor(
                            renderer,
                            pixel.red,
                            pixel.green,
                            pixel.blue,
                            SDL_ALPHA_OPAQUE
                        );

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