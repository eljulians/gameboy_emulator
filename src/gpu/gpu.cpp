#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include "spdlog/spdlog.h"
#include <chrono>

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

void GPU::update(uint8_t cycles, int time) {
    // TODO: when to lcdControl.updateCachedControl() ???

    int currentScanline = lcdControl._cachedCurrentScanline;

    //spdlog::debug("LCDC: 0x{0:x}", lcdControl.getLCDControlValue());
    //spdlog::debug("STAT: 0x{0:x}", lcdControl.getStatus());
    SpriteVector sprites;
    elapsedTime += time;

    if (currentScanline != lastDrawnScanline) {
        lastDrawnScanline = currentScanline;

        auto backgroundStart = std::chrono::system_clock::now();
        PixelColorVector pixelVector = backgroundBuffer.getScanlineViewportRow();
        auto backgroundEnd = std::chrono::system_clock::now();
        auto backgroundTime = (backgroundStart - backgroundEnd).count();
        //spdlog::info("Background fetch time: {}", backgroundTime);

        auto backgroundDrawStart = std::chrono::system_clock::now();
        for (int i = 0; i < pixelVector.size(); i++) {
            PixelColor pixel = pixelVector.at(i);
            SDL_SetRenderDrawColor(renderer, pixel.red, pixel.green, pixel.blue, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, currentScanline);
        }
        auto backgroundDrawEnd = std::chrono::system_clock::now();
        auto backgroundDrawTime = (backgroundDrawEnd  - backgroundDrawStart).count();
        //spdlog::info("Background draw time: {}", backgroundDrawTime);

        if (lcdControl.getSpriteDisplay()) {
            // TODO handle 8x16 sprites
            auto spriteFetchStart = std::chrono::system_clock::now();
            sprites = spriteClient.getSprites(currentScanline);
            auto spriteFetchEnd = std::chrono::system_clock::now();
            auto spriteFetchTime = (spriteFetchEnd  - spriteFetchStart   ).count();
            //spdlog::info("Sprite fetch time: {}", spriteFetchTime);
            for (auto& sprite : sprites) {
                auto spriteSize = lcdControl.getSpriteSize();
                if (currentScanline - sprite.y >= 0 && currentScanline - sprite.y <= spriteSize) {
                    auto spriteLine = currentScanline - sprite.y;

                    // TODO refactor this shit
                    int k = 0;
                    auto spriteDrawStart = std::chrono::system_clock::now();
                    for (int j = 7; j >= 0; j--) {
                        auto pixel = sprite.getPixel(j, spriteLine);
                        int opacity = SDL_ALPHA_OPAQUE;

                        if (pixel.red != 255) {
                            // Sprite white pixels are transparent
                            SDL_SetRenderDrawColor(
                                renderer,
                                pixel.red,
                                pixel.green,
                                pixel.blue,
                                SDL_ALPHA_OPAQUE
                            );

                            SDL_RenderDrawPoint(renderer, sprite.x+k, currentScanline);
                        }
                        k++;
                    }
                    auto spriteDrawEnd = std::chrono::system_clock::now();
                    auto spriteDrawTime = (spriteFetchEnd  - spriteFetchStart   ).count();
                    //spdlog::info("Sprite draw time: {}", spriteDrawTime);
                }
            }
        }

        if (currentScanline == 0) {
            elapsedFrames += 1;
        }

        if (currentScanline == 0) {
            auto renderStart = std::chrono::system_clock::now();
            SDL_RenderPresent(renderer);
            auto renderEnd = std::chrono::system_clock::now();
            auto renderTime = (renderEnd - renderStart ).count();
            //spdlog::info("Render time: {}", renderTime);
        }
    }

    if (elapsedTime > 1000000000) {
        elapsedTime = 0;
        //spdlog::info(elapsedFrames);
        elapsedFrames = 0;
    }

    auto updateStart = std::chrono::system_clock::now();
    lcdControl.update(cycles);
    auto updateEnd = std::chrono::system_clock::now();
    auto updateTime = (updateEnd - updateStart ).count();
    //spdlog::info("LCD Upate time: {}", updateTime);
}