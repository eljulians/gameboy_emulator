#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include "spdlog/spdlog.h"

#include <stdint.h>
#include "gpu.hpp"
#include "lcd_control.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "color.hpp"



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
    spdlog::debug("Scroll X: {}", backgroundBuffer.getScroll().x);
    spdlog::debug("Scroll Y: {}", backgroundBuffer.getScroll().y);

    if (currentScanline != lastDrawnScanline) {
        lastDrawnScanline = currentScanline;
        PixelColorVector pixelVector = backgroundBuffer.getScanlineViewportRow();
        spdlog::debug("Drawing scanline {}", currentScanline);

        for (int i = 0; i < pixelVector.size(); i++) {
            PixelColor pixel = pixelVector.at(i);
            SDL_SetRenderDrawColor(renderer, pixel.red, pixel.green, pixel.blue, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, currentScanline);
        }

        SDL_RenderPresent(renderer);
    }

    lcdControl.update(cycles);
}