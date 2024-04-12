
#include "spdlog/spdlog.h"
#include <iostream>
#include "mmu.hpp"
#include <vector>
#include <stdint.h>
#include <iostream>
#include "../gameboy.hpp"
#include "../cpu/timer/timer.hpp"
#include "../gpu/lcd_control.hpp"


MMU::MMU(GameBoy& gameBoy) : gameBoy(gameBoy) {
    internalRam = std::vector<uint8_t>(INTERNAL_RAM_SIZE);
    echo = std::vector<uint8_t>(ECHO_SIZE);
    spriteAttributes = std::vector<uint8_t>(SPRITE_ATTRIBUTES_SIZE);
    io = std::vector<uint8_t>(IO_SIZE);
    highRam = std::vector<uint8_t>(HIGH_RAM_SIZE);
    videoRam = std::vector<uint8_t>(VIDEO_RAM_SIZE);
    interrupt = 0x00;
    // TODO: implement switchable RAM banking
    switchableRam = std::vector<uint8_t>(SWITCHABLE_RAM_SIZE);
    notUsable = std::vector<uint8_t>(NOT_USABLE_SIZE);
}

void MMU::write_8bit(uint16_t address, uint8_t value) {
    if (IS_ROM_BANK_0(address) || IS_ROM_BANK_1(address)) {
        gameBoy.cartridge->write(address - ROM_BANK_0_START, value);
    }
    
    if (IS_VIDEO_RAM(address)) {
        videoRam.at(address - VIDEO_RAM_START) = value;
    }

    if (IS_SWITCHABLE_RAM(address)) {
        // TODO: implement switchable RAM banking
        switchableRam.at(address - SWITCHABLE_RAM_BANK_START) = value;
    }

    if (IS_INTERNAL_RAM(address)) {
        internalRam.at(address - INTERNAL_RAM_START) = value;
    }

    if(IS_ECHO(address)) {
        echo.at(address - ECHO_START) = value;
    }

    if (IS_SPRITE_ATTRIBUTES(address)) {
        spriteAttributes.at(address - SPRITE_ATTRIBUTES_START) = value;
    }

    if (IS_IO(address)) {

        if (address == 0xFF00) {
            spdlog::debug("Trying to write to $FF00; it's readonly");
            return;
        }

        if (address == 0xFF02 && (value == 0x81 || value == 0x80)) {
            std::cout << read_8bit(0xFF01);
        }
        /*
        if (address == 0xFF42) {
            io.at(address - IO_START) = value;
        }
        */

        if (address == DIVIDER_ADDRESS || address == CURRENT_SCANLINE_ADDRESS) {
            io.at(address - IO_START) = 0x00;
        } else {
            io.at(address - IO_START) = value;
        }
    }

    if (IS_HIGH_RAM(address)) {
        highRam.at(address - HIGH_RAM_START) = value;
    }

    if (IS_NOT_USABLE(address)) {
        notUsable.at(address - NOT_USABLE_START) = value;
    }
    
    if (IS_INTERRUPT(address)) {
        interrupt = value;
    }

    // OAM DMA transfer
    // TODO refactor somewhere
    if (address == 0xFF46) {
        uint16_t oamAddress = value << 8;
        for (int i = 0; i < 0xA0; i++) {
            write_8bit(0xFE00+i, read_8bit(oamAddress +i));
        }

    }
}

void MMU::write_16bit(uint16_t address, uint16_t value) {
    write_8bit(address, value & 0xFF);
    write_8bit(address + 0x01, value >> 8);
}

uint8_t MMU::read_8bit(uint16_t address) {

    if (IS_ROM_BANK_0(address) || IS_ROM_BANK_1(address)) {
        return gameBoy.cartridge->read(address);
    }
    
    if (IS_VIDEO_RAM(address)) {
        return videoRam.at(address - VIDEO_RAM_START);
    }

    if (IS_SWITCHABLE_RAM(address)) {
        // TODO: implement switchable RAM banking
        return switchableRam.at(address - SWITCHABLE_RAM_BANK_START);
    }

    if (IS_INTERNAL_RAM(address)) {
        return internalRam.at(address - INTERNAL_RAM_START);
    }

    if(IS_ECHO(address)) {
        // TODO - is it necessary to implement this?
        return echo.at(address - ECHO_START);
    }

    if (IS_SPRITE_ATTRIBUTES(address)) {
        return spriteAttributes.at(address - SPRITE_ATTRIBUTES_START);
    }

    if (IS_NOT_USABLE(address)) {
        return notUsable.at(address - NOT_USABLE_START);
    }

    if (IS_IO(address)) {
        if (address == 0xFF00) {
            // TODO joypad
            return 0xFF;
        }

        return io.at(address - IO_START);
    }

    if (IS_HIGH_RAM(address)) {
        return highRam.at(address - HIGH_RAM_START);
    }

    if (IS_INTERRUPT(address)) {
        return interrupt;
    }
}
