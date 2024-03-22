#include <fstream>
#include <string>
#include <iostream>
#include "cartridge.hpp"
#include <stdint.h>
#include <vector>
#include <filesystem>

#include "spdlog/spdlog.h"


AbstractCartridge* createCartridge(std::string romPath) {
    std::string currentPath = std::filesystem::current_path();
    std::string romAbsolutePath = currentPath + "/" + romPath;
    std::ifstream instream(romAbsolutePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());

    uint8_t type = data.at(CARTRIDGE_TYPE_HEADER);
    uint8_t romSizeCode = data.at(ROM_SIZE_ADDRESS);
    uint8_t ramSizeCode = data.at(RAM_SIZE_ADDRESS);

    int romSize = 32000 * (1 << romSizeCode);
    int ramSize = 0;

    // TODO this properly
    if (ramSizeCode == 2) {
        ramSize = 8000;
    } else if (ramSizeCode == 3) {
        ramSize = 32000;
    }

    AbstractCartridge* cartridge;

    switch(type) {
        case 0x00:
            spdlog::info("ROM only cartridge");
            cartridge = new CartridgeROMOnly(data, romSize, ramSize);

        case 0x01:
        case 0x02:  // TODO fix
            spdlog::info("MBC1 cartridge");
            cartridge = new CartridgeMBC1(data, romSize, ramSize);
    }

    spdlog::info("ROM size: {} KiB", (int)romSize/1000);
    spdlog::info("ROM banks: {}", (int)romSize/1000/16);
    spdlog::info("RAM size: {} KiB", (int)ramSize/1000);
    spdlog::info("RAM banks: {}", (int)ramSize/1000/8);

    return cartridge;
}

uint8_t AbstractCartridge::read(uint16_t address) {
    return rom.at(address);
}

void AbstractCartridge::write(uint16_t address, uint8_t value) {
    rom.at(address) = value;
}


int CartridgeROMOnly::getRomBankIndex(uint8_t address) {
    return 0;
}

int CartridgeROMOnly::getRamBankIndex(uint8_t address) {
    return 0;
}

int CartridgeMBC1::getRomBankIndex(uint8_t address) {
    if (0x0 < address && address <= 0x3FFF) {
        return 0;
    }
}

int CartridgeMBC1::getRamBankIndex(uint8_t address) {
    return 0;
}