#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdint.h>

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"
#include "../src/cpu/alu_8bit.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"


TEST_CASE("ADD_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("no flags") {
        f.set(0x00);
        a.set(0x00);
        b.set(0x01);
        alu_8bit->add_a_r8(b);

        REQUIRE(a.get() == 0x01);
        REQUIRE(f.get() == 0x00);
    }

    SECTION("zero, half carry and carry flags") {
        f.set(0x00);
        a.set(0xFF);
        b.set(0x01);
        alu_8bit->add_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 1);
    }

    SECTION("half carry flag") {
        f.set(0x00);
        a.set(0x0F);
        b.set(0x01);
        alu_8bit->add_a_r8(b);

        REQUIRE(a.get() == 0x10);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0x7000, 0x43);
        hl.set(0x7000);
        a.set(0x42);
        alu_8bit->add_a_hl();

        REQUIRE(a.get() == 0x85);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0x7000, 0x20);
       gameBoy.cpu.setPC(0x7000);
       a.set(0x20);
       alu_8bit->add_a_n8();

       REQUIRE(a.get() == 0x40);
       REQUIRE(gameBoy.cpu.getPC() == 0x7001);
    }
}

TEST_CASE("ADC_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    Flag* flags = new Flag(f);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);


    SECTION("unset carry") {
        f.set(0x00);
        a.set(0x00);
        b.set(0x01);

        alu_8bit->adc_a_r8(b);

        REQUIRE(a.get() == 0x01);
        REQUIRE(f.get() == 0x00);
    }

    SECTION("set carry, no other flags") {
        f.set(0x00);
        flags->set_c(1);
        a.set(0x00);
        b.set(0x01);
        alu_8bit->adc_a_r8(b);

        REQUIRE(a.get() == 0x02);
        REQUIRE(f.get() == 0x00);
    }

    SECTION("set carry, zero, half carry and carry flags") {
        f.set(0x00);
        flags->set_c(1);
        a.set(0xFE);
        b.set(0x01);
        alu_8bit->adc_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 1);
    }

    SECTION("unset carry, half carry flag") {
        f.set(0x00);
        a.set(0x0F);
        b.set(0x01);
        alu_8bit->adc_a_r8(b);

        REQUIRE(a.get() == 0x10);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0x7000, 0x43);
        hl.set(0x7000);
        flags->set_c(1);
        a.set(0x42);
        alu_8bit->adc_a_hl();

        REQUIRE(a.get() == 0x86);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0x7000, 0x20);
       gameBoy.cpu.setPC(0x7000);
       flags->set_c(1);
       a.set(0x20);
       alu_8bit->adc_a_n8();

       REQUIRE(a.get() == 0x41);
       REQUIRE(gameBoy.cpu.getPC() == 0x7001);
    }
}