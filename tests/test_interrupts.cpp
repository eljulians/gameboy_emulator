#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../src/gameboy.hpp"
#include "../src/interrupts/interrupts.hpp"

TEST_CASE("flag-unflag") {
    GameBoy gameBoy = GameBoy();
    InterruptHandler interrupt = InterruptHandler(gameBoy);

    SECTION("VBlank") {
        interrupt.flagVBlank();
        REQUIRE(interrupt.isVBlankFlagged());

        interrupt.unflagVBlank();
        REQUIRE(!interrupt.isVBlankFlagged());
    }
}