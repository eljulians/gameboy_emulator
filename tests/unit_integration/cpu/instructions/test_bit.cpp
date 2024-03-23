#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include "../lib/catch.hpp"
#include "../src/cpu/registers.hpp"
#include "../src/cpu/bit.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"

TEST_CASE("BIT", "[bit]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Bit bit = Bit(cpu);

    SECTION("z flag") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.bit(cpu.A, 7);

        REQUIRE(cpu.flags->get_z() == 1);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 1);
        REQUIRE(cpu.flags->get_c() == 0);
    }

    SECTION("no flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.bit(cpu.A, 6);

        REQUIRE(cpu.flags->get_z() == 0);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 1);
        REQUIRE(cpu.flags->get_c() == 0);
    }
}

TEST_CASE("SET", "[bit]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Bit bit = Bit(cpu);

    SECTION("no change") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.set(cpu.A, 6);

        REQUIRE(cpu.A.get() == 0b01000000);
    }

    SECTION("change") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.set(cpu.A, 7);

        REQUIRE(cpu.A.get() == 0b11000000);
    }
}

TEST_CASE("RES", "[bit]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Bit bit = Bit(cpu);

    SECTION("change") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.res(cpu.A, 6);

        REQUIRE(cpu.A.get() == 0b00000000);
    }

    SECTION("no change") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        bit.res(cpu.A, 7);

        REQUIRE(cpu.A.get() == 0b01000000);
    }
}