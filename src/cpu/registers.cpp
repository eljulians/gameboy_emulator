#include "registers.hpp"
#include <stdint.h>
#include <iostream>


uint8_t Register_8bit::get() {
    return value;
}


void Register_8bit::set(uint8_t val) {
    value = val;
}

void Register_8bit::increment() {
    value++;
}

void Register_8bit::decrement() {
    value--;
}


void Register_16bit::increment() {
    value++;
}

void Register_16bit::decrement() {
    value--;
}

uint8_t RegisterPair::getAddressValue() {
    return mmu.read_8bit(get());
}

void RegisterPair::setAddressValue(uint8_t value) {
    return mmu.write_8bit(get(), value);
}


uint16_t Register_16bit::get() {
    return value;
}

void Register_16bit::set(uint16_t newValue) {
    value = newValue;
}


void RegisterPair::set(uint16_t newValue) {
    high.set(newValue >> 8);
    low.set(newValue & 0xFF);
}

uint16_t RegisterPair::get() {
    return ((high.get() << 8) | low.get());
}


uint8_t RegisterPair::getLow() {
    return low.get();
}

uint8_t RegisterPair::getHigh() {
    return high.get();
}


void RegisterPair::setLow(uint8_t value) {
    low.set(value);
}

void RegisterPair::setHigh(uint8_t value) {
    high.set(value);
}

void RegisterPair::increment() {
    low.increment();
    
    if (low.get() == 0) {
        high.increment();
    }
}

void RegisterPair::decrement() {
    low.decrement();

    if (low.get() == 0xFF) {
        high.decrement();
    }
}

bool Flag::get_z() {
    return flag.get() >> 7;
}

bool Flag::get_n() {
    return (flag.get() >> 6) & 0x01;
}

bool Flag::get_h() {
    return (flag.get() >> 5) & 0x01;
}

bool Flag::get_c() {
    return (flag.get() >> 4) & 0x01;
}

void Flag::set_z(bool newFlag) {
    if (newFlag == 0) {
        flag.set(flag.get() & 0x7F);
    } else {
        flag.set(flag.get() | 0x80);
    }
}

void Flag::set_n(bool newFlag) {
    if (newFlag == 0) {
        flag.set(flag.get() & 0xBF);
    } else {
        flag.set(flag.get() | 0x40);
    }
}

void Flag::set_h(bool newFlag) {
    if (newFlag == 0) {
        flag.set(flag.get() & 0xDF);
    } else {
        flag.set(flag.get() | 0x20);
    }
}

void Flag::set_c(bool newFlag) {
    if (newFlag == 0) {
        flag.set(flag.get() & 0xEF);
    } else {
        flag.set(flag.get() | 0x10);
    }
}