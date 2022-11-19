#include <fstream>
#include <string>
#include <iostream>
#include "cartridge.hpp"
#include <stdint.h>
#include <vector>
#include <filesystem>


void CartridgeROMOnly::loadRom() {
    std::string currentPath = std::filesystem::current_path();
    std::string romAbsolutePath = currentPath + "/" + romPath;
    std::ifstream instream(romAbsolutePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    rom = data;
}

uint8_t CartridgeROMOnly::read(uint16_t address) {
    return rom.at(address);
}

void CartridgeROMOnly::write(uint16_t address, uint8_t value) {
    
}