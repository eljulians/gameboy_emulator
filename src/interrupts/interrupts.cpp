#include <stdint.h>
#include "interrupts.hpp"
#include "../gameboy.hpp"


uint8_t getInterruptMask(Interrupt interrupt) {
    return (1 << INTERRUPT_BIT_MAP.at(interrupt));
}

uint8_t InterruptHandler::getIF() {
    return gameBoy.mmu.read_8bit(IF_FLAG_ADDRESS);
}

uint8_t InterruptHandler::getIE() {
    return gameBoy.mmu.read_8bit(IE_FLAG_ADDRESS);
}

void InterruptHandler::setIF(uint8_t value) {
    gameBoy.mmu.write_8bit(IF_FLAG_ADDRESS, value);
}

void InterruptHandler::flagInterrupt(Interrupt interrupt) {
    setIF(getIF() | getInterruptMask(interrupt));
}

bool InterruptHandler::isInterruptEnabled(Interrupt interrupt) {
    return getIF() & getInterruptMask(interrupt);
}

void InterruptHandler::unflagInterrupt(Interrupt interrupt) {
    setIF(getIF() & ~getInterruptMask(interrupt));
}

void InterruptHandler::flagVBlank() {
    flagInterrupt(Interrupt::VBlank);
}

void InterruptHandler::flagLCDC() {

}

void InterruptHandler::flagTimer() {

}

void InterruptHandler::flagSerialTransfer() {

}

void InterruptHandler::flagKeypad() {

}

void InterruptHandler::unflagVBlank() {
    unflagInterrupt(Interrupt::VBlank);
}

void InterruptHandler::unflagLCDC() {

}

void InterruptHandler::unflagTimer() {

}

void InterruptHandler::unflagSerialTransfer() {

}

void InterruptHandler::unflagKeypad() {

}


bool InterruptHandler::isVBlankFlagged() {
    return getIF() & getInterruptMask(Interrupt::VBlank);
}