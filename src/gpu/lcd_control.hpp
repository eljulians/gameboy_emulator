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
    FIRST,   // $9800-$9BFF
    SECOND,  // $9C00-$9FFF
};

// TODO bit 5 (window display enable)

// Bit 4 of 0xFF40
enum class BackgroundAndWindowTileDataSelect {
    FIRST_SIGNED,   // $8800-$97FF
    SECOND_UNSIGNED,  // $8000-$8FFF, same area as OBJ
};

// Bit 3 of 0xFF40
enum class BackgroundTileMapDisplaySelect {
    FIRST,     // $9800-$9BFF
    SECOND,  // $9C00-$9FFF
};

// Bit 2 of 0xFF40
enum class SpriteSize {
    EIGHT_BY_EIGHT,
    EIGHT_BY_SIXTEEN,  // width * height
};

// TODO bits 1 and 0 (sprint and bg displays enable)

class LCDControl {
    public:
        LCDControl(MMU& mmu, InterruptManager& interruptManager) : mmu(mmu), interruptManager(interruptManager) {};
        void update(uint8_t cycles);
        bool isScreenOn(); // bit 7
        WindowTileMapDisplaySelect getWindowTileMapDisplaySelect();  // bit 6; TODO: remove
        int getWindowTileMapDisplaySelectAddress(); // bit 6
        bool getWindowDisplay(); // bit 5
        BackgroundAndWindowTileDataSelect getBackgroundAndWindowTileDataSelect(); // bit 4
        BackgroundTileMapDisplaySelect getBackgroundTileMapDisplaySelect(); // bit 3
        int getBackgroundLayoutAddress(); // bit 3
        SpriteSize getSpriteSize(); // bit 2
        bool getSpriteDisplay();  // bit 1
        bool getBackgroundAndWindowDisplay();  // bit 0
        uint8_t getCurrentScanline();

        uint8_t getLCDControlValue();
        uint8_t getStatus();


    private:
        MMU& mmu;
        InterruptManager& interruptManager;
        int currentCycles = 0;


        LCDMode getMode();
        void setMode(LCDMode mode);
        bool isModeInterruptEnabled(LCDMode mode);

        void setStatus(uint8_t value);

        void nextScanline();
        void resetScanline();
        void handleModeChange();
};