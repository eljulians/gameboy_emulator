#define CATCH_CONFIG_MAIN

#include <stdint.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include "spdlog/spdlog.h"

#include "../../lib/catch.hpp"
#include "../../src/cpu/registers.hpp"
#include "../../src/cpu/jumps.hpp"
#include "../../src/cpu/cpu.hpp"
#include "../../src/mmu/mmu.hpp"
#include "../../src/gameboy.hpp"

using json = nlohmann::json;

TEST_CASE("foo") {
    spdlog::set_level(spdlog::level::critical);

    GameBoy gameBoy = GameBoy();
    CPU& cpu = gameBoy.cpu;
    std::ifstream test_file("tests/jsmoo/test_files/01.json", std::ifstream::binary);
    json test = json::parse(test_file);

    for (auto& testCase : test) {
        SECTION(testCase.at("name")) {
            auto& setup = testCase.at("initial");
            auto& expected = testCase.at("final");
            cpu.PC.set(setup.at("pc"));
            cpu.SP.set(setup.at("sp"));
            cpu.A.set(setup.at("a"));
            cpu.B.set(setup.at("b"));
            cpu.C.set(setup.at("c"));
            cpu.D.set(setup.at("d"));
            cpu.E.set(setup.at("e"));
            cpu.F.set(setup.at("f"));
            cpu.H.set(setup.at("h"));
            cpu.L.set(setup.at("l"));

            for (auto& memory : setup.at("ram")) {
                gameBoy.mmu.write_8bit(memory.at(0), memory.at(1));
            }
            cpu.controlUnit.execute(); 

            REQUIRE(cpu.A.get() == expected.at("a"));
            REQUIRE(cpu.B.get() == expected.at("b"));
            REQUIRE(cpu.C.get() == expected.at("c"));
            REQUIRE(cpu.D.get() == expected.at("d"));
            REQUIRE(cpu.E.get() == expected.at("e"));
            REQUIRE(cpu.F.get() == expected.at("f"));
            REQUIRE(cpu.H.get() == expected.at("h"));
            REQUIRE(cpu.L.get() == expected.at("l"));

            for (auto& memory : expected.at("ram")) {
                REQUIRE(gameBoy.mmu.read_8bit(memory.at(0)) == memory.at(1));
            }

            REQUIRE(cpu.PC.get() == expected.at("pc"));
            REQUIRE(cpu.SP.get() == expected.at("sp"));
        }
    }
}