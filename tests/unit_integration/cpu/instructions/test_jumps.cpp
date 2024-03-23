#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include "../lib/catch.hpp"
#include "../src/cpu/registers.hpp"
#include "../src/cpu/jumps.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"

TEST_CASE("JP_NN") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.PC.set(0xC000);
    gameBoy.mmu.write_8bit(0xC000, 0x20);
    gameBoy.mmu.write_8bit(0xC001, 0x40);

    jumps.jp_nn();

    REQUIRE(cpu.PC.get() == 0x4020);
}

TEST_CASE("JP_HL") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.HL->set(0xC050);

    jumps.jp_hl();

    REQUIRE(cpu.PC.get() == 0xC050);
}


TEST_CASE("CALL_NN") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.PC.set(0xC000);
    gameBoy.mmu.write_8bit(0xC000, 0x40);
    gameBoy.mmu.write_8bit(0xC001, 0x60);
    gameBoy.mmu.write_8bit(0xC002, 0x70);
    gameBoy.mmu.write_8bit(0xC003, 0x80);

    jumps.call_nn();

    REQUIRE(gameBoy.mmu.read_8bit(0xFFFD) == 0xC0);
    REQUIRE(gameBoy.mmu.read_8bit(0xFFFC) == 0x02);
    REQUIRE(cpu.PC.get() == 0x6040);
}


TEST_CASE("RET_NN") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    Jumps jumps = Jumps(cpu);

    cpu.PC.set(0xC000);
    gameBoy.mmu.write_8bit(0xFFFD, 0xAE);
    gameBoy.mmu.write_8bit(0xFFFC, 0x15);
    cpu.SP.set(0xFFFC);

    jumps.ret();

    REQUIRE(cpu.PC.get() == 0xAE15);
}