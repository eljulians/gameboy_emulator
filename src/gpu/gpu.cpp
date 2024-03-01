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

    //window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //surface = SDL_GetWindowSurface(window);

    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderClear(renderer);
    //SDL_RenderPresent(renderer);

    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(window);
}

void GPU::update(uint8_t cycles) {
    PixelColorVector pixelVector = backgroundBuffer.getScanlineViewportRow();
    int currentScanline = lcdControl.getCurrentScanline();

    spdlog::info("LCDC: 0x{0:x}", lcdControl.getLCDControlValue());
    spdlog::info("STAT: 0x{0:x}", lcdControl.getStatus());

    if (currentScanline != lastDrawnScanline) {
        lastDrawnScanline = currentScanline;
        spdlog::info("Drawing scanline {}", currentScanline);

        for (int i = 0; i < pixelVector.size(); i++) {
            PixelColor pixel = pixelVector.at(i);
            SDL_SetRenderDrawColor(renderer, pixel.red, pixel.green, pixel.blue, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, currentScanline);
        }

        SDL_RenderPresent(renderer);
    }
    lcdControl.update(cycles);
}