#include <stdint.h>
#include "gpu.hpp"
#include "lcd_control.hpp"
#include "tile.hpp"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 140


void GPU::init_sdl() {
    SDL_Init(SDL_INIT_VIDEO);


    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    //SDL_UpdateWindowSurface(window);
}

void GPU::update(uint8_t cycles) {
}