#define CATCH_CONFIG_MAIN

#include "../../lib/catch.hpp"

#include "../../src/common/bit_operations.hpp"

TEST_CASE("testBit", "[bit_operations]") {
    REQUIRE(testBit(0b11100101, 7) == 1);
    REQUIRE(testBit(0b11100101, 6) == 1);
    REQUIRE(testBit(0b11100101, 5) == 1);
    REQUIRE(testBit(0b11100101, 4) == 0);
    REQUIRE(testBit(0b11100101, 3) == 0);
    REQUIRE(testBit(0b11100101, 2) == 1);
    REQUIRE(testBit(0b11100101, 1) == 0);
    REQUIRE(testBit(0b11100101, 0) == 1);
}