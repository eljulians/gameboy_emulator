#include <iostream>
#include <string>
#include "gameboy.hpp"


int main(int argc, char *argv[]) {
    //std::string romPath = argv[1];
    std::string romPath = "roms/03-op_sp,hl.gb";
    GameBoy gameBoy = GameBoy(romPath);
    gameBoy.mainLoop();
}