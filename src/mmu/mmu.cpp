#include "mmu.hpp"
#include <vector>
#include <stdint.h>
#include "../gameboy.hpp"


MMU::MMU(GameBoy& gameBoy) : gameBoy(gameBoy) {
    ram = std::vector<uint8_t>(0x8000);
    internalRam = std::vector<uint8_t>(INTERNAL_RAM_SIZE);
    spriteAttributes = std::vector<uint8_t>(SPRITE_ATTRIBUTES_SIZE);
    io = std::vector<uint8_t>(IO_SIZE);
    highRam = std::vector<uint8_t>(HIGH_RAM_SIZE);
    interrupt = 0x00;
}

void MMU::write_8bit(uint16_t address, uint8_t value) {
    // TODO: ROM
    if (IS_ROM_BANK_1(address)) {
        ram.at(address) = value;
    }
    
    if (IS_VIDEO_RAM(address)) {
        
    }

    if (IS_SWITCHABLE_RAM(address)) {

    }

    if (IS_INTERNAL_RAM(address)) {
        internalRam.at(address - INTERNAL_RAM_START) = value;
    }

    if (IS_SPRITE_ATTRIBUTES(address)) {

    }

    if (IS_IO(address)) {
    }

    if (IS_HIGH_RAM(address)) {
        highRam.at(address - HIGH_RAM_START) = value;
    }

    if (IS_INTERRUPT(address)) {

    }
}

void MMU::write_16bit(uint16_t address, uint16_t value) {
    ram.at(address) = value & 0xFF;
    ram.at(address + 0x01) = value >> 8;
}

uint8_t MMU::read_8bit(uint16_t address) {
    // TODO: read from cartridge
    if (IS_ROM_BANK_1(address)) {
        return ram.at(address);
    }
    
    if (IS_VIDEO_RAM(address)) {
        
    }

    if (IS_SWITCHABLE_RAM(address)) {

    }

    if (IS_INTERNAL_RAM(address)) {
        return internalRam.at(address - INTERNAL_RAM_START);
    }

    if (IS_SPRITE_ATTRIBUTES(address)) {

    }

    if (IS_IO(address)) {

    }

    if (IS_HIGH_RAM(address)) {
        return highRam.at(address - HIGH_RAM_START);
    }

    if (IS_INTERRUPT(address)) {

    }
}