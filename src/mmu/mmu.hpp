#pragma once
#include <stdint.h>
#include <vector>

#define ROM_BANK_0_START 0x0000
#define ROM_BANK_0_END 0x3FFF
#define IS_ROM_BANK_0(a) a <= ROM_BANK_0_END
#define ROM_BANK_0_SIZE (ROM_BANK_0_END - ROM_BANK_0_START + 1)

#define ROM_BANK_1_START 0x4000
#define ROM_BANK_1_END 0x7FFF
#define ROM_BANK_1_SIZE (ROM_BANK_1_END - ROM_BANK_1_START + 1)
#define IS_ROM_BANK_1(a) ROM_BANK_1_START <= a && a <= ROM_BANK_1_END

#define VIDEO_RAM_START 0x8000
#define VIDEO_RAM_END 0x9FFF
#define VIDEO_RAM_SIZE (VIDEO_RAM_END - VIDEO_RAM_START + 1)
#define IS_VIDEO_RAM(a) VIDEO_RAM_START <= address && address <= VIDEO_RAM_END

#define SWITCHABLE_RAM_BANK_START 0xA000
#define SWITCHABLE_RAM_BANK_END 0xBFFF
#define SWITCHABLE_RAM_SIZE (SWITCHABLE_RAM_BANK_END - SWITCHABLE_RAM_BANK_START + 1)
#define IS_SWITCHABLE_RAM(a) SWITCHABLE_RAM_BANK_START <= a && a <= SWITCHABLE_RAM_BANK_END

#define INTERNAL_RAM_START 0xC000
#define INTERNAL_RAM_END 0xDFFF
#define INTERNAL_RAM_SIZE (INTERNAL_RAM_END - INTERNAL_RAM_START + 1)
#define IS_INTERNAL_RAM(a) INTERNAL_RAM_START <= a && a <= INTERNAL_RAM_END

#define SPRITE_ATTRIBUTES_START 0xFE00
#define SPRITE_ATTRIBUTES_END 0xFE9F
#define SPRITE_ATTRIBUTES_SIZE (SPRITE_ATTRIBUTES_END - SPRITE_ATTRIBUTES_START + 1)
#define IS_SPRITE_ATTRIBUTES(address) SPRITE_ATTRIBUTES_START <= address && address <= SPRITE_ATTRIBUTES_END

#define IO_START 0xFF00
#define IO_END 0xFF4B
#define IO_SIZE (IO_END - IO_START + 1)
#define IS_IO(address) IO_START <= address && address <= IO_END

#define HIGH_RAM_START 0xFF80
#define HIGH_RAM_END 0xFFFE
#define HIGH_RAM_SIZE (HIGH_RAM_END - HIGH_RAM_START + 1)
#define IS_HIGH_RAM(address) HIGH_RAM_START <= address && address <= HIGH_RAM_END

#define INTERRUPT_REGISTER 0xFFFF
#define IS_INTERRUPT(address) address == INTERRUPT_REGISTER


class GameBoy;

class MMU {
private:
    GameBoy& gameBoy;
    std::vector<uint8_t> ram;
    std::vector<uint8_t> internalRam;
    std::vector<uint8_t> spriteAttributes;
    std::vector<uint8_t> io;
    std::vector<uint8_t> highRam;
    std::vector<uint8_t> videoRam;
    // TODO: implement switchable RAM banking
    std::vector<uint8_t> switchableRam;
    uint8_t interrupt;

public:
    MMU(GameBoy& gameBoy);
    uint8_t read_8bit(uint16_t address);
    uint16_t read_16bit(uint16_t address);
    void write_8bit(uint16_t address, uint8_t value);
    void write_16bit(uint16_t address, uint16_t value);
};