#include <stdint.h>
#include "loads_8bit.hpp"
#include "registers.hpp"
#include "cpu.hpp"


uint8_t Loads8bit::load_r8_n8(Register_8bit& register_) {
    register_.set(cpu.fetchByte());

    return 8;
}


uint8_t Loads8bit::load_r8_r8(Register_8bit& to, Register_8bit& from) {
    to.set(from.get());

    return 4;
}

uint8_t Loads8bit::load_r8_hl(Register_8bit& to) {
    to.set(hl.getAddressValue());

    return 8;
}

uint8_t Loads8bit::load_hl_r8(Register_8bit& from) {
    hl.setAddressValue(from.get());

    return 8;
}

int Loads8bit::load_hl_d8() {
    cpu.HL->setAddressValue(cpu.fetchByte());

    return 12;
}


int8_t Loads8bit::load_a_r16(RegisterPair& register_) {
    cpu.A.set(register_.getAddressValue());

    return 8;
}

int8_t Loads8bit::load_a_address() {
    uint16_t address = cpu.fetch2bytes();
    cpu.A.set(mmu.read_8bit(address));

    return 16;
}


int8_t Loads8bit::load_r16_a(RegisterPair& register_) {
    mmu.write_8bit(register_.get(), cpu.A.get());

    return 8;
}

int8_t Loads8bit::load_a16_a() {
    uint16_t address = cpu.fetch2bytes();
    mmu.write_8bit(address, cpu.A.get());

    return 16;
}

void Loads8bit::load_a_c() {
    uint16_t address = 0xFF00 + cpu.C.get();
    cpu.A.set(mmu.read_8bit(address));
}

void Loads8bit::load_c_a() {
    uint16_t address = 0xFF00 + cpu.C.get();
    mmu.write_8bit(address, cpu.A.get());
}

int8_t Loads8bit::ld_hl_a_decrement() {
    cpu.HL->setAddressValue(cpu.A.get());
    cpu.HL->decrement();

    return 8;
}

int8_t Loads8bit::ld_a_hl_increment() {
    cpu.A.set(cpu.HL->getAddressValue());
    cpu.HL->increment();

    return 8;
}

int8_t Loads8bit::ld_hl_a_increment() {
    cpu.HL->setAddressValue(cpu.A.get());
    cpu.HL->increment();

    return 8;
}

int8_t Loads8bit::ldh_n_a() {
    uint16_t address = 0xFF00 + cpu.fetchByte();    
    mmu.write_8bit(address, cpu.A.get());

    return 12;
}

int8_t Loads8bit::ldh_a_n() {
    uint16_t address = 0xFF00 + cpu.fetchByte();    
    cpu.A.set(mmu.read_8bit(address));

    return 12;
}


int8_t Loads8bit::ld_r16_n16(RegisterPair register_) {
    register_.set(cpu.fetch2bytes());

    return 12;
}

int8_t Loads8bit::ld_sp_hl() {
    cpu.SP.set(cpu.HL->get());

    return 12;
}

int8_t Loads8bit::ld_hl_sp_n() {
    int8_t value = cpu.fetchSignedByte();
    int result = static_cast<int>(cpu.SP.get() + value);

    cpu.flags->set_z(0);
    cpu.flags->set_n(0);
    cpu.flags->set_h(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    cpu.flags->set_c(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    hl.set(static_cast<uint16_t>(result));

    return 12;
}

int8_t Loads8bit::ld_n16_sp() {
    mmu.write_16bit(cpu.fetch2bytes(), cpu.SP.get());

    return 20;
}

int8_t Loads8bit::ld_sp_n16() {
    cpu.SP.set(cpu.fetch2bytes());

    return 12;
}

uint8_t Loads8bit::push_r16(RegisterPair register_) {
    cpu.push_onto_stack(register_.getHigh());
    cpu.push_onto_stack(register_.getLow());

    return 16;
}

uint8_t Loads8bit::pop_r16(RegisterPair register_) {
    uint8_t low = cpu.pop_from_stack();
    uint8_t high = cpu.pop_from_stack();

    register_.setLow(low);
    register_.setHigh(high);

    return 12;
}

int8_t Loads8bit::ld_a_c() {
    uint16_t address = 0xFF00 + cpu.C.get();
    cpu.A.set(mmu.read_8bit(address));

    return 8;
}

int8_t Loads8bit::ld_c_a() {
    uint16_t address = 0xFF00 + cpu.C.get();
    mmu.write_8bit(address, cpu.A.get());

    return 8;
}