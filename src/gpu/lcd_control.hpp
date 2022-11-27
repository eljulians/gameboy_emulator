#pragma once

#include <stdint.h>
#include <map>

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

class LCDControl {
    public:
        LCDControl(MMU& mmu, InterruptManager& interruptManager) : mmu(mmu), interruptManager(interruptManager) {};
        void update(uint8_t cycles);


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