#define CATCH_CONFIG_MAIN
#include <iostream>

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"
#include "../src/cpu/alu_8bit.hpp"


TEST_CASE("ADD_A", "[alu_8bit]") {
    Register_8bit a, b, f;
    Flag* flags = new Flag(f);
    ALU_8bit* alu_8bit = new ALU_8bit(a, *flags);

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

}

TEST_CASE("ADC_A", "[alu_8bit]") {
    Register_8bit a, b, f;
    Flag* flags = new Flag(f);
    ALU_8bit* alu_8bit = new ALU_8bit(a, *flags);

    SECTION("unset carry") {
        f.set(0x00);
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
}