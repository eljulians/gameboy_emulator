#include <stdint.h>

#include "lcd_control.hpp"
#include "../mmu/mmu.hpp"
#include "../interrupts/interrupt_manager.hpp"


uint8_t LCDControl::getCurrentScanline() {
    return mmu.read_8bit(CURRENT_SCANLINE_ADDRESS);
}

uint8_t LCDControl::getStatus() {
    return mmu.read_8bit(LCD_STATUS_ADDRESS); 
}

void LCDControl::setStatus(uint8_t value) {
    mmu.write_8bit(LCD_STATUS_ADDRESS, value); 
}

LCDMode LCDControl::getMode() {
    uint8_t mode = getStatus() & 0x3;

    return static_cast<LCDMode>(mode);
}

void LCDControl::setMode(LCDMode mode) {
    uint8_t status = (getStatus() & 0xFC) | static_cast<uint8_t>(mode);

    setStatus(status);
}

bool LCDControl::isModeInterruptEnabled(LCDMode mode) {
    uint8_t modeInterrupts = getStatus() >> 2;
    uint8_t modeShift = static_cast<uint8_t>(mode);

    return (modeInterrupts >> modeShift) & 1;
}

void LCDControl::nextScanline() {
    mmu.write_8bit(CURRENT_SCANLINE_ADDRESS, getCurrentScanline() + 1);
}

void LCDControl::resetScanline() {
    mmu.write_8bit(CURRENT_SCANLINE_ADDRESS, 0);
}

void LCDControl::handleModeChange() {
    LCDMode previousMode = getMode();
    LCDMode currentMode;

    if (IS_OAM_SEARCH(currentCycles)) {
        currentMode = LCDMode::OAMSearch;
    } else if (IS_LCD_TRANSFER(currentCycles)) {
        currentMode = LCDMode::LCDTransfer;
    } else if (IS_HBLANK(currentCycles)) {
        currentMode = LCDMode::HBlank;
    }

    if (currentMode != previousMode) {
        // LCD Transfer mode doesn't have interrupt bit, so???
        if (currentMode == LCDMode::LCDTransfer || isModeInterruptEnabled(currentMode))  {
            interruptManager.lcdc.flag();
        }
    }

}

void LCDControl::update(uint8_t cycles) {
    currentCycles += cycles;

    if (currentCycles >= CYCLES_TO_DRAW_SCANLINE) {
        currentCycles = 0;
        nextScanline();
    }

    if (getCurrentScanline() < VISIBLE_SCANLINES) {
        handleModeChange();
    } else if (getCurrentScanline() == VISIBLE_SCANLINES and currentCycles == 0) {
        setMode(LCDMode::VBlank);
        if (isModeInterruptEnabled(LCDMode::VBlank)) {
            interruptManager.vblank.flag();
        }
    } else if (VISIBLE_SCANLINES < getCurrentScanline() && getCurrentScanline() <= TOTAL_SCANLINES) {

    } else if (TOTAL_SCANLINES < getCurrentScanline()) {
        resetScanline();
        currentCycles = 0;
    }
}


uint8_t LCDControl::getLCDControlValue() {
    return mmu.read_8bit(LCD_CONTROL_ADDRESS);
}

bool LCDControl::isScreenOn() {
    return testBit(getLCDControlValue(), 7);
}

WindowTileMapDisplaySelect LCDControl::getWindowTileMapDisplaySelect() {
    return static_cast<WindowTileMapDisplaySelect>(testBit(getLCDControlValue(), 6));
}

bool LCDControl::getWindowDisplay() {
    return testBit(getLCDControlValue(), 5);
}

BackgroundAndWindowTileDataSelect LCDControl::getBackgroundAndWindowTileDataSelect() {
    return static_cast<BackgroundAndWindowTileDataSelect>(testBit(getLCDControlValue(), 4));
}

BackgroundTileMapDisplaySelect LCDControl::getBackgroundTileMapDisplaySelect() {
    return static_cast<BackgroundTileMapDisplaySelect>(testBit(getLCDControlValue(), 3));
}

SpriteSize LCDControl::getSpriteSize() {
    return static_cast<SpriteSize>(testBit(getLCDControlValue(), 2));
}

bool LCDControl::getSpriteDisplay() {
    return testBit(getLCDControlValue(), 1);
}

bool LCDControl::getBackgroundAndWindowDisplay() {
    return testBit(getLCDControlValue(), 0);
}