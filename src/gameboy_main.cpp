#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_thread.h>

#include "gameboy.hpp"


#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 140

int threadFunction(void* data) {
    std::cout << "Hello from thread";

    return 0;
}

int main(int argc, char *argv[]) {
    //std::string romPath = argv[1];
    std::string romPath = "roms/tetris.gb";
    GameBoy gameBoy = GameBoy(romPath);

    /*
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Event e;
    bool quit = false; 

    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    */

    gameBoy.mainLoop();
}