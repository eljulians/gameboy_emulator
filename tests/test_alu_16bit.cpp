#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"
#include "../src/cpu/alu_16bit.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"


TEST_CASE("ADD_HL_n", "[alu_16bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit b, c, h, l, f;
    Flag flags = Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    RegisterPair bc = RegisterPair(gameBoy.mmu, b, c);
    Register_16bit sp = Register_16bit();
    ALU_16bit alu = ALU_16bit(gameBoy.cpu, hl, sp, flags);

    SECTION("no flags") {
        f.set(0x00);
        hl.set(0x0001);
        bc.set(0x0020);
        alu.add_hl_r16(bc);

        REQUIRE(hl.get() == 0x21);
        REQUIRE(f.get() == 0x00);
    }

    SECTION("zero, half carry and carry flags") {
        f.set(0x00);
        hl.set(0xFFFF);
        bc.set(0x0001);
        alu.add_hl_r16(bc);

        REQUIRE(hl.get() == 0x00);
        REQUIRE(flags.get_z() == 1);
        REQUIRE(flags.get_n() == 0);
        REQUIRE(flags.get_h() == 1);
        REQUIRE(flags.get_c() == 1);
    }

    SECTION("half carry") {
        f.set(0x00);
        hl.set(0xFFF);
        bc.set(0x1);
        alu.add_hl_r16(bc);

        REQUIRE(hl.get() == 0x1000);
        REQUIRE(flags.get_z() == 0);
        REQUIRE(flags.get_n() == 0);
        REQUIRE(flags.get_h() == 1);
        REQUIRE(flags.get_c() == 0);
    }
}


TEST_CASE("ADD_SP_s8", "[alu_16bit]") {
    GameBoy gameBoy = GameBoy();
    Register_8bit b, c, h, l, f;
    Flag flags = Flag(f);
    RegisterPair hl = RegisterPair(gameBoy.mmu, h, l);
    RegisterPair bc = RegisterPair(gameBoy.mmu, b, c);
    Register_16bit sp = Register_16bit();
    ALU_16bit alu = ALU_16bit(gameBoy.cpu, hl, sp, flags);

    SECTION("no flags") {
        f.set(0x00);
        gameBoy.cpu.setSP(0xFFF0);
        gameBoy.cpu.setPC(0x7000);
        gameBoy.mmu.write_8bit(0x7000, 0x01);

        alu.add_sp_s8();

        REQUIRE(gameBoy.cpu.getSP() == 0xFFF1);
        REQUIRE(f.get() == 0x00);
    }

    SECTION("negative, carry flag") {
        f.set(0x00);
        gameBoy.cpu.setSP(0xFFF0);
        gameBoy.cpu.setPC(0x7000);
        gameBoy.mmu.write_8bit(0x7000, -0x01);

        alu.add_sp_s8();

        REQUIRE(gameBoy.cpu.getSP() == 0xFFEF);
        REQUIRE(flags.get_z() == 0);
        REQUIRE(flags.get_n() == 0);
        REQUIRE(flags.get_h() == 0);
        REQUIRE(flags.get_c() == 1);
    }

    SECTION("negative, half and carry flags") {
        f.set(0x00);
        gameBoy.cpu.setSP(0xFFFF);
        gameBoy.cpu.setPC(0x7000);
        gameBoy.mmu.write_8bit(0x7000, -0x01);

        alu.add_sp_s8();

        REQUIRE(gameBoy.cpu.getSP() == 0xFFFE);
        REQUIRE(flags.get_z() == 0);
        REQUIRE(flags.get_n() == 0);
        REQUIRE(flags.get_h() == 1);
        REQUIRE(flags.get_c() == 1);
    }

    SECTION("overflow") {
        f.set(0x00);
        gameBoy.cpu.setSP(0xFFFE);
        gameBoy.cpu.setPC(0x7000);
        gameBoy.mmu.write_8bit(0x7000, 0x02);

        alu.add_sp_s8();

        REQUIRE(gameBoy.cpu.getSP() == 0x0);
        REQUIRE(flags.get_z() == 0);
        REQUIRE(flags.get_n() == 0);
        REQUIRE(flags.get_h() == 1);
        REQUIRE(flags.get_c() == 1);
    }
}