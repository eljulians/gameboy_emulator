#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"

#include "../src/gameboy.hpp"
#include "../src/interrupts/interrupt.hpp"

TEST_CASE("flag-unflag") {
    GameBoy gameBoy = GameBoy();
    Interrupt vblank = Interrupt(gameBoy.mmu, InterruptEnum::VBlank);

    gameBoy.mmu.write_8bit(IF_FLAG_ADDRESS, 0x00);

    SECTION("flag") {
        vblank.flag();
        REQUIRE(vblank.isFlagged());
        REQUIRE(gameBoy.mmu.read_8bit(IF_FLAG_ADDRESS) == 0x01);
    }

    SECTION("unflag") {
        vblank.unflag();
        REQUIRE(!vblank.isFlagged());
        REQUIRE(gameBoy.mmu.read_8bit(IF_FLAG_ADDRESS) == 0x00);
    }
}


TEST_CASE("enable-disale") {
    GameBoy gameBoy = GameBoy();
    Interrupt timer = Interrupt(gameBoy.mmu, InterruptEnum::Timer);

    gameBoy.mmu.write_8bit(IE_FLAG_ADDRESS, 0x00);

    SECTION("flag") {
        timer.enable();
        REQUIRE(timer.isEnabled());
        REQUIRE(gameBoy.mmu.read_8bit(IE_FLAG_ADDRESS) == 0x04);
    }

    SECTION("unflag") {
        timer.disable();
        REQUIRE(!timer.isEnabled());
        REQUIRE(gameBoy.mmu.read_8bit(IE_FLAG_ADDRESS) == 0x00);
    }
}