#pragma once

#include <string>
#include <stdint.h>
#include <vector>

#define ROM_ONLY_SIZE 0x8000


class CartridgeROMOnly {
    private:
        std::string romPath;
        std::vector<uint8_t> rom;

    public:
        CartridgeROMOnly() {rom = std::vector<uint8_t>(0x8000);};
        CartridgeROMOnly(std::string romPath) : romPath(romPath) {};
        void loadRom();
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
};