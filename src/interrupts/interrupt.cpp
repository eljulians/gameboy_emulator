#include <stdint.h>
#include "interrupt.hpp"
#include "../mmu/mmu.hpp"


uint8_t getInterruptMask(InterruptEnum interrupt) {
    return (1 << INTERRUPT_BIT_MAP.at(interrupt));
}

uint8_t Interrupt::getIF() {
    return mmu.read_8bit(IF_FLAG_ADDRESS);
}

uint8_t Interrupt::getIE() {
    return mmu.read_8bit(IE_FLAG_ADDRESS);
}

void Interrupt::setIF(uint8_t value) {
    mmu.write_8bit(IF_FLAG_ADDRESS, value);
}

void Interrupt::setIE(uint8_t value) {
    mmu.write_8bit(IE_FLAG_ADDRESS, value);
}

void Interrupt::flag() {
    setIF(getIF() | getInterruptMask(interruptEnum));
}

void Interrupt::unflag() {
    setIF(getIF() & ~getInterruptMask(interruptEnum));
}

bool Interrupt::isFlagged() {
    return getIF() & getInterruptMask(interruptEnum);
}

void Interrupt::enable() {
    setIE(getIE() | getInterruptMask(interruptEnum));
}

void Interrupt::disable() {
    setIE(getIE() & ~getInterruptMask(interruptEnum));
}

bool Interrupt::isEnabled() {
    return getIE() & getInterruptMask(interruptEnum);
}

int8_t Interrupt::getAddress() {
    return INTERRUPT_ADDRESS_MAP.at(interruptEnum);
}

char* Interrupt::toString() {
    str(interruptEnum);
}