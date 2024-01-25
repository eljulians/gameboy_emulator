#pragma once

#include <stdint.h>
#include <map>

#include "../common/bit_operations.hpp"

#define LCD_CONTROL_ADDRESS 0xFF40
#define LCD_STATUS_ADDRESS 0xFF41
#define CURRENT_SCANLINE_ADDRESS 0xFF44

#define VISIBLE_SCANLINES 144
#define TOTAL_SCANLINES 153
#define CYCLES_TO_DRAW_SCANLINE 456

#define IS_OAM_SEARCH(cycles) 0 <= cycles &&  cycles < 80
#define IS_LCD_TRANSFER(cycles) 80 <= cycles && cycles < 252
#define IS_HBLANK(cycles) 252 <= cycles && cycles < VISIBLE_SCANLINES


class MMU;
class InterruptManager;

enum class LCDMode {
    HBlank,
    VBlank,
    OAMSearch,
    LCDTransfer,
};

// Bit 6 of 0xFF40
enum class WindowTileMapDisplaySelect {
    FIRST,   // $9800-$9BFF, unsiged 0,128
    SECOND,  // $9C00-$9FFF, signed -128,127
};

// Bit 4 of 0xFF40
enum class BackgroundAndWindowTileDataSelect {
    FIRST,   // $8000-$97FF
    SECOND,  // $8000-$8FFF, same area as OBJ
};

// Bit 3 of 0xFF40
enum class BackgroundTileMapDisplaySelect {
    FIRST_SIGNED,     // $9800-$9BFF, unsiged 0,128
    SECOND_UNSIGNED,  // $9C00-$9FFF, signed -128,127
};

// Bit 2 of 0xFF40
enum class SpriteSize {
    EIGHT_BY_EIGHT,
    EIGHT_BY_SIXTEEN,  // width * height
};

class LCDControl {
    public:
        LCDControl(MMU& mmu, InterruptManager& interruptManager) : mmu(mmu), interruptManager(interruptManager) {};
        void update(uint8_t cycles);
        bool isScreenOn(); // bit 7
        WindowTileMapDisplaySelect getWindowTileMapDisplaySelect();  // bit 6
        bool getWindowDisplay(); // bit 5
        BackgroundAndWindowTileDataSelect getBackgroundAndWindowTileDataSelect(); // bit 4
        BackgroundTileMapDisplaySelect getBackgroundTileMapDisplaySelect(); // bit 3
        SpriteSize getSpriteSize(); // bit 2
        bool getSpriteDisplay();  // bit 1
        bool getBackgroundAndWindowDisplay();  // bit 0

        uint8_t getLCDControlValue();


    private:
        MMU& mmu;
        InterruptManager& interruptManager;
        uint8_t currentCycles = 0;

        uint8_t getCurrentScanline();

        LCDMode getMode();
        void setMode(LCDMode mode);
        bool isModeInterruptEnabled(LCDMode mode);

        uint8_t getStatus();
        void setStatus(uint8_t value);

        void nextScanline();
        void resetScanline();
        void handleModeChange();
};