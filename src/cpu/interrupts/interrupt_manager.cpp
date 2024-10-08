#include <stdint.h>
#include <iostream>
#include <vector>

#include "spdlog/spdlog.h"

#include "interrupt.hpp"
#include "interrupt_manager.hpp"
#include "../cpu.hpp"
#include "../../mmu/mmu.hpp"


InterruptVector InterruptManager::getInterrupts() {
    return {vblank, lcdc, timer, serial, keypad};
}

bool InterruptManager::handle() {
    /*
    Conditions for interrupts to occur:
    1. Global IME master interrupt is enabled (currently attribute of CPU)
    2. Specific interrupt is enabled  ($0xFFFF, wrapped by Interrupt class)
    3. Interrupt has been flagged ($0xFF0F, wrapped by Interrupt class)

    Interrupt order matters!
    */
    // TODO?: move attribute to this class instead?
    if (!cpu.areInterruptsEnabled()) {
        return false;
    }

    for (Interrupt interrupt : {vblank, lcdc, timer, serial, keypad}) {
        if (interrupt.isEnabled() && interrupt.isFlagged()) {
            auto address = interrupt.getAddress();
            auto currentPC = cpu.PC.get();
            //std::cout << interrupt.toString() << " enabled and flagged, jumping to  " << std::hex << address;
            //std::cout << " and pushing " << std::hex << currentPC << " onto stack";
            //std::cout << interrupt.toString();

            //spdlog::info("AF 0x{0:x}", cpu.AF->get());
            

            // TODO: this is just a CALL, probably should refactor
            cpu.push_address_onto_stack(currentPC);
            cpu.PC.set(address);

            cpu.disableInterrupts();
            interrupt.unflag();

            return true;
        }
    }

    return false;
}