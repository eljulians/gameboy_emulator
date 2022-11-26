#pragma once
#include <map>
#include <stdint.h>

// Interrupt flag - interrupt condition was met
#define IF_FLAG_ADDRESS 0xFF0F

// Interrupt enabled flag - individual interrupts (no IME master)
#define IE_FLAG_ADDRESS 0xFFFF


class MMU;

enum class InterruptEnum {
    VBlank,
    LCDC,
    Timer,
    SerialTransfer,
    Keypad,
};

typedef std::map<InterruptEnum, int8_t> interruptMap;

const interruptMap INTERRUPT_BIT_MAP = {
    {InterruptEnum::VBlank, 0},
    {InterruptEnum::LCDC, 1},
    {InterruptEnum::Timer, 2},
    {InterruptEnum::SerialTransfer, 3},
    {InterruptEnum::Keypad, 4},
};

const interruptMap INTERRUPT_ADDRESS_MAP = {
    {InterruptEnum::VBlank, 0x40},
    {InterruptEnum::LCDC, 0x48},
    {InterruptEnum::Timer, 0x50},
    {InterruptEnum::SerialTransfer, 0x58},
    {InterruptEnum::Keypad, 0x60},
};


class Interrupt {
    public:
        Interrupt(MMU& mmu, InterruptEnum interruptEnum) :
            mmu(mmu),
            interruptEnum(interruptEnum)
        {};

        void flag();
        void unflag();
        bool isFlagged();

        void enable();
        void disable();
        bool isEnabled();

    protected:
        MMU& mmu;
        InterruptEnum interruptEnum;

        uint8_t getIF();
        uint8_t getIE();
        void setIF(uint8_t value);
        void setIE(uint8_t value);
};


class InterruptHandler {
    public:
        InterruptHandler(MMU& mmu) : 
            mmu(mmu),
            vblank(mmu, InterruptEnum::VBlank),
            lcdc(mmu, InterruptEnum::LCDC),
            timer(mmu, InterruptEnum::Timer),
            serial(mmu, InterruptEnum::SerialTransfer),
            keypad(mmu, InterruptEnum::Keypad)
        {};
        Interrupt vblank;
        Interrupt lcdc;
        Interrupt timer;
        Interrupt serial;
        Interrupt keypad;

    private:
        MMU& mmu;
        void flagInterrupt(InterruptEnum interrupt);
        void unflagInterrupt(InterruptEnum interrupt);
        bool isInterruptFlagged(InterruptEnum interrupt);

        void enableInterrupt(InterruptEnum interrupt);
        void disableInterrupt(InterruptEnum interrupt);
        bool isInterruptEnabled(InterruptEnum interrupt);
};