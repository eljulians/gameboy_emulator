#include <iostream>
#include <string>
#include "gameboy.hpp"


int main(int argc, char *argv[]) {
    //std::string romPath = argv[1];
    std::string romPath = "roms/cpu_instrs.gb";
    GameBoy gameBoy = GameBoy(romPath);
    gameBoy.mainLoop();
}