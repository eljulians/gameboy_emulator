#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"
#include "../src/cpu/jumps.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"

TEST_CASE("JP_NN") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.PC.set(0x7000);
    gameBoy.mmu.write_8bit(0x7000, 0x20);
    gameBoy.mmu.write_8bit(0x7001, 0x40);

    jumps.jp_nn();

    REQUIRE(cpu.PC.get() == 0x4020);
}

TEST_CASE("JP_HL") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.HL->set(0x3050);

    jumps.jp_hl();

    REQUIRE(cpu.PC.get() == 0x3050);
}

TEST_CASE("CALL_NN") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.PC.set(0x7000);
    gameBoy.mmu.write_8bit(0x7000, 0x40);
    gameBoy.mmu.write_8bit(0x7001, 0x60);

    jumps.call_nn();

    //REQUIRE(gameBoy.mmu.read_16bit(cpu.SP.get()) == 0x6040);
    REQUIRE(cpu.PC.get() == 0x7002);
    REQUIRE(cpu.SP.get() == 0xFFFC);
}