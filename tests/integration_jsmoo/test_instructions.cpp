#define CATCH_CONFIG_MAIN

#include <stdint.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <stdint.h>

#include "spdlog/spdlog.h"

#include "../../lib/catch.hpp"
#include "../../src/gameboy.hpp"

std::string testFilesPath = "./tests/integration_jsmoo/test_files/";

using json = nlohmann::json;


std::string getOpcodeName(std::string path) {
    std::string fileName = path.replace(
        path.find(testFilesPath),
        testFilesPath.length(),
        ""
    );
    std::string opcode = fileName.replace(
        fileName.find(".json"),
        5,
        ""
    );

    return opcode;
}

// TOOD: figure out how to generate test cases dynamically, one for each opcode
TEST_CASE("CPU") {
    spdlog::set_level(spdlog::level::critical);

    GameBoy gameBoy = GameBoy();
    CPU& cpu = gameBoy.cpu;

    for (const auto& entry : std::filesystem::directory_iterator(testFilesPath)) {
        std::string path = (std::string)entry.path();
        std::cout << path << std::endl;

        std::ifstream test_file(path, std::ifstream::binary);
        json test = json::parse(test_file);

        for (auto& testCase : test) {
            std::string testCaseName = (std::string)testCase.at("name");

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
                uint16_t address = (uint16_t)memory.at(0);
                // Direct writes to addresses that would be reset by hardware
                if (address == DIVIDER_ADDRESS || address == CURRENT_SCANLINE_ADDRESS) {
                    gameBoy.mmu.io.at(address - IO_START) = memory.at(1);
                }
                else {
                    gameBoy.mmu.write_8bit(address, memory.at(1));
                }
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
            REQUIRE(cpu.PC.get() == expected.at("pc"));
            REQUIRE(cpu.SP.get() == expected.at("sp"));

            // Assert memory addresses
            for (auto& memory : expected.at("ram")) {
                uint16_t expectedAddress = (uint16_t)memory.at(0);
                // Don't bother making assertions on addresses that would be reset by hardware upon
                // direct write, e.g. test case E2 00AC doing LD $FF44 r8
                if (expectedAddress  == DIVIDER_ADDRESS || expectedAddress  == CURRENT_SCANLINE_ADDRESS) {
                    continue;
                }

                REQUIRE(gameBoy.mmu.read_8bit(memory.at(0)) == memory.at(1));
            }

            // Reset halt state to prevent coupling
            cpu.halted = false;
        }
    } 
}