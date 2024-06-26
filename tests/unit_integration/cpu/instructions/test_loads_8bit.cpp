#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdint.h>

#include "../lib/catch.hpp"
#include "../src/cpu/registers.hpp"
#include "../src/cpu/loads_8bit.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"

TEST_CASE("LOAD_R8_N8", "[loads_8bit]") {
    GameBoy gameBoy = GameBoy(); 
    Register_8bit a, h, l;
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    Loads8bit loads = Loads8bit(gameBoy.cpu, gameBoy.mmu, hl);
    uint16_t pc = 0xC000;
    uint8_t value = 0x40;
    gameBoy.cpu.setPC(pc);
    gameBoy.mmu.write_8bit(pc, value);

    loads.load_r8_n8(a);

    REQUIRE(a.get() == value);
}

TEST_CASE("LOAD_R8_R8", "[loads_8bit]") {
    GameBoy gameBoy = GameBoy(); 
    Register_8bit a, b, h, l;
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    Loads8bit loads = Loads8bit(gameBoy.cpu, gameBoy.mmu, hl);

    a.set(0x00);
    b.set(0xFA);

    loads.load_r8_r8(a, b);

    REQUIRE(a.get() == b.get());
}

TEST_CASE("LOAD_R8_HL", "[loads_8bit]") {
    GameBoy gameBoy = GameBoy(); 
    Register_8bit a, h, l;
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    Loads8bit loads = Loads8bit(gameBoy.cpu, gameBoy.mmu, hl);

    a.set(0x00);
    hl.set(0xC000);
    gameBoy.mmu.write_8bit(0xC000, 0xAE);

    loads.load_r8_hl(a);

    REQUIRE(a.get() == 0xAE);
}