#pragma once
#include <stdint.h>
#include <vector>

class GameBoy;

class MMU {
private:
    GameBoy& gameBoy;
    std::vector<uint8_t> ram;

public:
    MMU(GameBoy& gameBoy);
    uint8_t read_8bit(uint16_t address);
    uint16_t read_16bit(uint16_t address);
    void write_8bit(uint16_t address, uint8_t value);
    void write_16bit(uint16_t address, uint16_t value);
};