#include "mmu.hpp"
#include <vector>
#include <stdint.h>
#include "../gameboy.hpp"


MMU::MMU(GameBoy& gameBoy) : gameBoy(gameBoy) {
    ram = std::vector<uint8_t>(0x8000);
}