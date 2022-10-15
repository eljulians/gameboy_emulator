#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"
#include "../src/cpu/rotates.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"


TEST_CASE("RLCA", "[rotates]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Rotates rotates = Rotates(cpu);

    SECTION("no flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        rotates.rlca();

        REQUIRE(cpu.A.get() == 0b10000000);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("z flag") {
        cpu.F.set(0x00);
        cpu.A.set(0b00000000);

        rotates.rlca();

        REQUIRE(cpu.A.get() == 0x00);
        REQUIRE(cpu.flags->get_z() == 1);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 0);
    }

    SECTION("z, c flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b10000000);

        rotates.rlca();

        REQUIRE(cpu.A.get() == 0x00);
        REQUIRE(cpu.flags->get_z() == 1);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 1);
    }
}

TEST_CASE("RLA", "[rotates]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Rotates rotates = Rotates(cpu);

    SECTION("no flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        rotates.rla();

        REQUIRE(cpu.A.get() == 0b10000000);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("c set") {
        cpu.F.set(0x00);
        cpu.flags->set_c(1);
        cpu.A.set(0b00000000);

        rotates.rla();

        REQUIRE(cpu.A.get() == 0x01);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("c set, c flags") {
        cpu.F.set(0x00);
        cpu.flags->set_c(1);
        cpu.A.set(0b10000000);

        rotates.rla();

        REQUIRE(cpu.A.get() == 0x01);
        REQUIRE(cpu.flags->get_z() == 0);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 1);
    }
}

TEST_CASE("RRCA", "[rotates]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Rotates rotates = Rotates(cpu);

    SECTION("no flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b00000010);

        rotates.rrca();

        REQUIRE(cpu.A.get() == 0x01);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("z flag") {
        cpu.F.set(0x00);
        cpu.A.set(0x00);

        rotates.rrca();

        REQUIRE(cpu.A.get() == 0x00);
        REQUIRE(cpu.flags->get_z() == 1);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 0);
    }

    SECTION("z, c flags") {
        cpu.F.set(0x00);
        cpu.A.set(0x01);

        rotates.rrca();

        REQUIRE(cpu.A.get() == 0x00);
        REQUIRE(cpu.flags->get_z() == 1);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 1);
    }
}

TEST_CASE("RRA", "[rotates]") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Rotates rotates = Rotates(cpu);

    SECTION("no flags") {
        cpu.F.set(0x00);
        cpu.A.set(0b01000000);

        rotates.rra();

        REQUIRE(cpu.A.get() == 0b00100000);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("c set") {
        cpu.F.set(0x00);
        cpu.flags->set_c(1);
        cpu.A.set(0b00000000);

        rotates.rra();

        REQUIRE(cpu.A.get() == 0x80);
        REQUIRE(cpu.F.get() == 0x00);
    }

    SECTION("c set, c flags") {
        cpu.F.set(0x00);
        cpu.flags->set_c(1);
        cpu.A.set(0b00000001);

        rotates.rra();

        REQUIRE(cpu.A.get() == 0x80);
        REQUIRE(cpu.flags->get_z() == 0);
        REQUIRE(cpu.flags->get_n() == 0);
        REQUIRE(cpu.flags->get_h() == 0);
        REQUIRE(cpu.flags->get_c() == 1);
    }
}