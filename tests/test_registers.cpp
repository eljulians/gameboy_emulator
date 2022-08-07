#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "../src/cpu/registers.hpp"


TEST_CASE("Register pair operation", "[registers]") {
    Register_8bit a, b;
    RegisterPair* registerPair = new RegisterPair(a, b);


    SECTION("Setter and getter") {
        registerPair->set(0xAE12);
        REQUIRE(registerPair->get() == 0xAE12);
    }

    SECTION("Increment") {
        registerPair->set(0xAE12);
        registerPair->increment();
        REQUIRE(registerPair->get() == 0xAE13);
        
        registerPair->set(0xAEFF);
        registerPair->increment();
        REQUIRE(registerPair->get() == 0xAF00);

        registerPair->set(0xFFFF);
        registerPair->increment();
        REQUIRE(registerPair->get() == 0x0000);
    }

    SECTION("Decrement") {
        registerPair->set(0xAE12);
        registerPair->decrement();
        REQUIRE(registerPair->get() == 0xAE11);
        
        registerPair->set(0xAE00);
        registerPair->decrement();
        REQUIRE(registerPair->get() == 0xADFF);

        registerPair->set(0x0000);
        registerPair->decrement();
        REQUIRE(registerPair->get() == 0xFFFF);
    }
}