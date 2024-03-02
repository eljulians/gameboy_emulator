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
    std::string romPath = "roms/cpu_instrs.gb";
    //std::string romPath = "roms/tetris.gb";
    GameBoy gameBoy = GameBoy(romPath);

    gameBoy.mmu.write_8bit(0xFF05, 0x00);
    gameBoy.mmu.write_8bit(0xFF06, 0x00);
    gameBoy.mmu.write_8bit(0xFF07, 0x00);
    gameBoy.mmu.write_8bit(0xFF10, 0x80);
    gameBoy.mmu.write_8bit(0xFF11, 0xBF);
    gameBoy.mmu.write_8bit(0xFF12, 0xF3);
    gameBoy.mmu.write_8bit(0xFF14, 0xBF);
    gameBoy.mmu.write_8bit(0xFF16, 0x3F);
    gameBoy.mmu.write_8bit(0xFF17, 0x00);
    gameBoy.mmu.write_8bit(0xFF19, 0xBF);
    gameBoy.mmu.write_8bit(0xFF1A, 0x7F);
    gameBoy.mmu.write_8bit(0xFF1B, 0xFF);
    gameBoy.mmu.write_8bit(0xFF1C, 0x9F);
    gameBoy.mmu.write_8bit(0xFF1E, 0xBF);
    gameBoy.mmu.write_8bit(0xFF20, 0xFF);
    gameBoy.mmu.write_8bit(0xFF21, 0x00);
    gameBoy.mmu.write_8bit(0xFF22, 0x00);
    gameBoy.mmu.write_8bit(0xFF23, 0xBF);
    gameBoy.mmu.write_8bit(0xFF24, 0x77);
    gameBoy.mmu.write_8bit(0xFF25, 0xF3);
    gameBoy.mmu.write_8bit(0xFF26, 0xF1);
    gameBoy.mmu.write_8bit(0xFF40, 0x91);
    //gameBoy.mmu.write_8bit(0xFF41, 0x81);
    gameBoy.mmu.write_8bit(0xFF42, 0x00);
    gameBoy.mmu.write_8bit(0xFF43, 0x00);
    gameBoy.mmu.write_8bit(0xFF45, 0x00);
    gameBoy.mmu.write_8bit(0xFF47, 0xFC);
    gameBoy.mmu.write_8bit(0xFF48, 0xFF);
    gameBoy.mmu.write_8bit(0xFF49, 0xFF);
    gameBoy.mmu.write_8bit(0xFF4A, 0x00);
    gameBoy.mmu.write_8bit(0xFF4B, 0x00);
    gameBoy.mmu.write_8bit(0xFFFF, 0x00);

    gameBoy.mainLoop();

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

}