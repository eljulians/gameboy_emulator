#include <stdint.h>

#include "spdlog/spdlog.h"

#include "lcd_control.hpp"
#include "../mmu/mmu.hpp"
#include "../cpu/interrupts/interrupt_manager.hpp"
#include "../common/bit_operations.hpp"


uint8_t LCDControl::getCurrentScanlineFromMemory() {
    return mmu.read_8bit(CURRENT_SCANLINE_ADDRESS);
}

uint8_t LCDControl::getStatus() {
    return mmu.read_8bit(LCD_STATUS_ADDRESS); 
}

void LCDControl::setStatus(uint8_t value) {
    mmu.write_8bit(LCD_STATUS_ADDRESS, value); 
}

LCDMode LCDControl::getModeFromMemory() {
    uint8_t mode = getStatus() & 0x3;

    return static_cast<LCDMode>(mode);
}

void LCDControl::setMode(LCDMode mode) {
    uint8_t status = (getStatus() & 0xFC) | static_cast<uint8_t>(mode);

    // No bit 7 on STAT, so will be an open bus that will be 1; making sure that it's set
    // to that just in case it was overriden
    // TODO: make this check directly on the MMU and make writes from here directly into
    // the address, also to ensure that the lower 2 bits are not overwritten since they're
    // read only
    status |= 1 << 7;

    setStatus(status);
}

void LCDControl::setCoincidence() {
    int isCoincidence = _cachedCurrentScanline == mmu.read_8bit(LY_COMPARE_ADDRESS);
    //int isCoincidence = getCurrentScanlineFromMemory() == mmu.read_8bit(LY_COMPARE_ADDRESS);
    uint8_t status = getStatus();
    setStatus(status | (isCoincidence << 2));

    if (isCoincidence &&  isCoincidenceInterruptEnabled()) {
        interruptManager.lcdc.flag();
    }
}

bool LCDControl::isModeInterruptEnabled(LCDMode mode) {
    uint8_t modeInterrupts = getStatus() >> 3;
    uint8_t modeShift = static_cast<uint8_t>(mode);

    return (modeInterrupts >> modeShift) & 1;
}

bool LCDControl::isCoincidenceInterruptEnabled() {
    return testBit(getStatus(), 6);
}

void LCDControl::nextScanline() {
    // Writing directly since otherwise it's reset to 0
    _cachedCurrentScanline++;
    mmu.io.at(CURRENT_SCANLINE_ADDRESS - IO_START) = _cachedCurrentScanline;
    //mmu.io.at(CURRENT_SCANLINE_ADDRESS - IO_START) = getCurrentScanlineFromMemory() + 1;
}

void LCDControl::resetScanline() {
    _cachedCurrentScanline = 0;
    mmu.write_8bit(CURRENT_SCANLINE_ADDRESS, 0);
}

void LCDControl::handleModeChange() {
    LCDMode currentMode;

    if (_cachedCurrentScanline >= VISIBLE_SCANLINES) {
    //if (getCurrentScanlineFromMemory() >= VISIBLE_SCANLINES) {
        currentMode = LCDMode::VBlank;
    } else {
        if (IS_OAM_SEARCH(currentCycles)) {
            currentMode = LCDMode::OAMSearch;
        } else if (IS_LCD_TRANSFER(currentCycles)) {
            currentMode = LCDMode::LCDTransfer;
        } else if (IS_HBLANK(currentCycles)) {
            currentMode = LCDMode::HBlank;
        } else {
            // We went past 456, so we start over
            currentMode = LCDMode::OAMSearch;
        }
    }

    if (currentMode != _cachedMode) {
        setMode(currentMode);
        _cachedMode = currentMode;

        if (currentMode == LCDMode::VBlank) {
            interruptManager.vblank.flag();
        }
        if (currentMode != LCDMode::LCDTransfer && isModeInterruptEnabled(currentMode)) {
            interruptManager.lcdc.flag();
        }
    }
}

void LCDControl::update(int cycles) {
    currentCycles += cycles * 4;

    /*
    spdlog::debug("STAT 0x{0:X}", mmu.read_8bit(0xFF41));
    spdlog::debug("LCDC 0x{0:X}", mmu.read_8bit(0xFF40));
    spdlog::debug("LY 0x{0:X}", mmu.read_8bit(0xFF44));
    */

    // FIgure out what to do here damn, definitely not just return
    if (!isScreenOn()) {
        // Apparently mode must be set to 1 when disabled
        //spdlog::info("off");
        //resetScanline();
        setMode(LCDMode::VBlank);
        //return;
    }

    handleModeChange();
    setCoincidence();

    if (currentCycles >= CYCLES_TO_DRAW_SCANLINE) {
        currentCycles -= CYCLES_TO_DRAW_SCANLINE;
        nextScanline();
    }

    if (_cachedCurrentScanline > TOTAL_SCANLINES) {
    //if (getCurrentScanlineFromMemory() > TOTAL_SCANLINES) {
        resetScanline();
        currentCycles -= CYCLES_TO_DRAW_SCANLINE;
    }
}


uint8_t LCDControl::getLCDControlValue() {
    return _cachedControl;
}

uint8_t LCDControl::getLCDControlValueFromMemory() {
    return mmu.read_8bit(LCD_CONTROL_ADDRESS);
}

void LCDControl::updateCachedControl() {
    _cachedControl = getLCDControlValueFromMemory();
}

bool LCDControl::isScreenOn() {
    return testBit(getLCDControlValue(), 7);
}

// TODO: remove, unused
void LCDControl::setScreenOn() {
    uint8_t control = getLCDControlValue();
    control = (1<<7) | control;
    mmu.write_8bit(LCD_CONTROL_ADDRESS, control);
}

WindowTileMapDisplaySelect LCDControl::getWindowTileMapDisplaySelect() {
    // TODO: remove and supersede with getWindowTileMapDisplaySelectAddress
    return static_cast<WindowTileMapDisplaySelect>(testBit(getLCDControlValue(), 6));
}


int LCDControl::getWindowTileMapDisplaySelectAddress() {
    auto enabled = testBit(getLCDControlValue(), 6);

    if (enabled) {
        return 0x9C00; 
    }

    return 0x9800; 
}

bool LCDControl::getWindowDisplay() {
    return testBit(getLCDControlValue(), 5);
}

BackgroundAndWindowTileDataSelect LCDControl::getBackgroundAndWindowTileDataSelect() {
    return static_cast<BackgroundAndWindowTileDataSelect>(testBit(getLCDControlValue(), 4));
}

BackgroundTileMapDisplaySelect LCDControl::getBackgroundTileMapDisplaySelect() {
    // TODO remove and supersede with getBackgroundTileMapDisplaySelectAddress
    return static_cast<BackgroundTileMapDisplaySelect>(testBit(getLCDControlValue(), 3));
}

int LCDControl::getBackgroundLayoutAddress() {
    auto enabled = testBit(getLCDControlValue(), 3);

    if (enabled) {
        return 0x9C00; 
    }

    return 0x9800;
}

int LCDControl::getSpriteSize() {
    SpriteSize size =  static_cast<SpriteSize>(testBit(getLCDControlValue(), 2));

    if (size == SpriteSize::EIGHT_BY_EIGHT) {
        return 8;
    }

    return 16;
}

bool LCDControl::getSpriteDisplay() {
    return testBit(getLCDControlValue(), 1);
}

bool LCDControl::getBackgroundAndWindowDisplay() {
    return testBit(getLCDControlValue(), 0);
}