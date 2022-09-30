#include "mmu.hpp"
#include <vector>
#include <stdint.h>
#include "../gameboy.hpp"


MMU::MMU(GameBoy& gameBoy) : gameBoy(gameBoy) {
    ram = std::vector<uint8_t>(0x8000);
}

void MMU::write_8bit(uint16_t address, uint8_t value) {
    ram.at(address) = value;
}

uint8_t MMU::read_8bit(uint16_t address) {
    return ram.at(address);
}