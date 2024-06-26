#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdint.h>

#include "../lib/catch.hpp"
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
        gameBoy.mmu.write_8bit(0xC000, 0x43);
        hl.set(0xC000);
        a.set(0x42);
        alu_8bit->add_a_hl();

        REQUIRE(a.get() == 0x85);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       alu_8bit->add_a_n8();

       REQUIRE(a.get() == 0x40);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
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
        gameBoy.mmu.write_8bit(0xC000, 0x43);
        hl.set(0xC000);
        flags->set_c(1);
        a.set(0x42);
        alu_8bit->adc_a_hl();

        REQUIRE(a.get() == 0x86);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       flags->set_c(1);
       a.set(0x20);
       alu_8bit->adc_a_n8();

       REQUIRE(a.get() == 0x41);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("SUB_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("no flags") {
        f.set(0x00);
        a.set(0x04);
        b.set(0x03);
        alu_8bit->sub_a_r8(b);

        REQUIRE(a.get() == 0x01);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("zero, no other flags") {
        f.set(0x00);
        a.set(0x00);
        b.set(0x00);
        alu_8bit->sub_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("half carry and carry flags") {
        f.set(0x00);
        a.set(0x9B);
        b.set(0xAC);
        alu_8bit->sub_a_r8(b);

        REQUIRE(a.get() == 0xEF);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 1);
    }

    SECTION("half carry") {
        f.set(0x00);
        a.set(0xAB);
        b.set(0x0C);
        alu_8bit->sub_a_r8(b);

        REQUIRE(a.get() == 0x9F);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        a.set(0x42);
        alu_8bit->sub_a_hl();

        REQUIRE(a.get() == 0x20);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       alu_8bit->sub_a_n8();

       REQUIRE(a.get() == 0x00);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("SBC_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("set carry") {
        f.set(0x00);
        flags->set_c(1);
        a.set(0x04);
        b.set(0x03);
        alu_8bit->sbc_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("unset carry") {
        f.set(0x00);
        a.set(0x04);
        b.set(0x03);
        alu_8bit->sbc_a_r8(b);

        REQUIRE(a.get() == 0x01);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        a.set(0x42);
        flags->set_c(1);
        alu_8bit->sbc_a_hl();

        REQUIRE(a.get() == 0x1F);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       flags->set_c(1);
       alu_8bit->sbc_a_n8();

       REQUIRE(a.get() == 0xFF);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("AND_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("r8") { 
        a.set(0x45);
        b.set(0x00);
        f.set(0x00);
        alu_8bit->and_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        a.set(0x42);
        alu_8bit->and_a_hl();

        REQUIRE(a.get() == 0x02);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       alu_8bit->and_a_n8();

       REQUIRE(a.get() == 0x20);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("OR_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("r8") { 
        a.set(0x00);
        b.set(0x00);
        f.set(0x00);
        alu_8bit->or_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        a.set(0x42);
        alu_8bit->or_a_hl();

        REQUIRE(a.get() == 0x62);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       alu_8bit->or_a_n8();

       REQUIRE(a.get() == 0x20);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("XOR_A", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, b, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("r8") { 
        a.set(0xFF);
        b.set(0xFF);
        f.set(0x00);
        alu_8bit->xor_a_r8(b);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        a.set(0x42);
        alu_8bit->xor_a_hl();

        REQUIRE(a.get() == 0x60);
    }

    SECTION("n8") {
       gameBoy.mmu.write_8bit(0xC000, 0x20);
       gameBoy.cpu.setPC(0xC000);
       a.set(0x20);
       alu_8bit->xor_a_n8();

       REQUIRE(a.get() == 0x00);
       REQUIRE(gameBoy.cpu.getPC() == 0xC001);
    }
}

TEST_CASE("INC_R8", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("no half carry") { 
        a.set(0x00);
        f.set(0x00);
        alu_8bit->inc_r8(a);

        REQUIRE(a.get() == 0x01);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("half carry") { 
        a.set(0x0F);
        f.set(0x00);
        alu_8bit->inc_r8(a);

        REQUIRE(a.get() == 0x10);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("half carry, zero") { 
        a.set(0xFF);
        f.set(0x00);
        alu_8bit->inc_r8(a);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 0);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        alu_8bit->inc_hl();

        REQUIRE(gameBoy.mmu.read_8bit(0xC000) == 0x23);
    }
}

TEST_CASE("DEC_R8", "[alu_8bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit a, h, l, f;
    Flag* flags = new Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    ALU_8bit* alu_8bit = new ALU_8bit(gameBoy.cpu, a, hl, *flags);

    SECTION("no flags") {
        f.set(0x00);
        a.set(0x02);
        alu_8bit->dec_r8(a);

        REQUIRE(a.get() == 0x01);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("zero, no other flags") {
        f.set(0x00);
        a.set(0x01);
        alu_8bit->dec_r8(a);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("half carry") {
        f.set(0x00);
        a.set(0xF0);
        alu_8bit->dec_r8(a);

        REQUIRE(a.get() == 0xEF);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("half carry, overflow") {
        f.set(0x00);
        a.set(0x00);
        alu_8bit->dec_r8(a);

        REQUIRE(a.get() == 0xFF);
        REQUIRE(flags->get_z() == 0);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 1);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("zero") {
        f.set(0x00);
        a.set(0x01);
        alu_8bit->dec_r8(a);

        REQUIRE(a.get() == 0x00);
        REQUIRE(flags->get_z() == 1);
        REQUIRE(flags->get_n() == 1);
        REQUIRE(flags->get_h() == 0);
        REQUIRE(flags->get_c() == 0);
    }

    SECTION("HL") {
        gameBoy.mmu.write_8bit(0xC000, 0x22);
        hl.set(0xC000);
        alu_8bit->dec_hl();

        REQUIRE(gameBoy.mmu.read_8bit(0xC000) == 0x21);
    }
}