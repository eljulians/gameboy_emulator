#define CATCH_CONFIG_MAIN
#include <stdint.h>

#include "../lib/catch.hpp"
#include "../src/cpu/registers.hpp"
#include "../src/cpu/jumps.hpp"
#include "../src/cpu/cpu.hpp"
#include "../src/mmu/mmu.hpp"
#include "../src/gameboy.hpp"


TEST_CASE("stack_push_and_pop") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;

    REQUIRE(cpu.SP.get() == 0xFFFE);

    cpu.push_address_onto_stack(0x0123);
    cpu.push_address_onto_stack(0x4560);

    REQUIRE(cpu.SP.get() == 0xFFFA);
    REQUIRE(cpu.pop_address_from_stack() == 0x4560);
    REQUIRE(cpu.pop_address_from_stack() == 0x0123);
    REQUIRE(cpu.SP.get() == 0xFFFE);
}

TEST_CASE("getCondition") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;

    SECTION("Z") {
        cpu.flags->set_z(true);

        REQUIRE(cpu.getCondition(Condition::Z));
        REQUIRE(!cpu.getCondition(Condition::NZ));
    }

    SECTION("NZ") {
        cpu.flags->set_z(false);

        REQUIRE(cpu.getCondition(Condition::NZ));
        REQUIRE(!cpu.getCondition(Condition::Z));
    }

    SECTION("C") {
        cpu.flags->set_c(true);

        REQUIRE(cpu.getCondition(Condition::C));
        REQUIRE(!cpu.getCondition(Condition::NC));
    }

    SECTION("NC") {
        cpu.flags->set_c(false);

        REQUIRE(cpu.getCondition(Condition::NC));
        REQUIRE(!cpu.getCondition(Condition::C));
    }
}