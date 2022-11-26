#pragma once
#include <map>
#include <stdint.h>

// Interrupt flag - interrupt condition was met
#define IF_FLAG_ADDRESS 0xFF0F

// Interrupt enabled flag - individual interrupts (no IME master)
#define IE_FLAG_ADDRESS 0xFFFF


class GameBoy;

enum class Interrupt {
    VBlank,
    LCDC,
    Timer,
    SerialTransfer,
    Keypad,
};

typedef std::map<Interrupt, int8_t> interruptMap;

const interruptMap INTERRUPT_BIT_MAP = {
    {Interrupt::VBlank, 0},
    {Interrupt::LCDC, 1},
    {Interrupt::Timer, 2},
    {Interrupt::SerialTransfer, 3},
    {Interrupt::Keypad, 4},
};

const interruptMap INTERRUPT_ADDRESS_MAP = {
    {Interrupt::VBlank, 0x40},
    {Interrupt::LCDC, 0x48},
    {Interrupt::Timer, 0x50},
    {Interrupt::SerialTransfer, 0x58},
    {Interrupt::Keypad, 0x60},
};

class InterruptHandler {
    public:
        InterruptHandler(GameBoy& gameBoy) : gameBoy(gameBoy) {};
        void flagVBlank();
        void flagLCDC();
        void flagTimer();
        void flagSerialTransfer(); 
        void flagKeypad();

        void unflagVBlank();
        void unflagLCDC();
        void unflagTimer();
        void unflagSerialTransfer(); 
        void unflagKeypad();

        void enableVBlank();
        void enableLCDC();
        void enableTimer();
        void enableSerialTransfer(); 
        void enableKeypad();

        void disableVBlank();
        void disableLCDC();
        void disableTimer();
        void disableSerialTransfer(); 
        void disableKeypad();

        bool isVBlankFlagged();
        bool isLCDCFlagged();
        bool isTimerFlagged();
        bool isSerialTransferFlagged(); 
        bool isKeypadFlagged();

    private:
        GameBoy& gameBoy;
        void flagInterrupt(Interrupt interrupt);
        void unflagInterrupt(Interrupt interrupt);
        bool isInterruptFlagged(Interrupt interrupt);

        void enableInterrupt(Interrupt interrupt);
        void disableInterrupt(Interrupt interrupt);
        bool isInterruptEnabled(Interrupt interrupt);
        uint8_t getIF();
        uint8_t getIE();
        void setIF(uint8_t value);
        void setIE(uint8_t value);
};