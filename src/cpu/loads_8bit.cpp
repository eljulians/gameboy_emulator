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


void Loads8bit::load_a_r8(Register_8bit& register_) {
    cpu.A.set(register_.get());
}

void Loads8bit::load_a_r16(RegisterPair& register_) {
    cpu.A.set(register_.getAddressValue());
}

void Loads8bit::load_a_n8() {
    cpu.A.set(cpu.fetchByte());
}

void Loads8bit::load_a_address() {
    uint16_t address = cpu.fetch2bytes();
    cpu.A.set(mmu.read_8bit(address));
}


void Loads8bit::load_r8_a(Register_8bit& register_) {
    register_.set(cpu.A.get());
}

void Loads8bit::load_r16_a(RegisterPair& register_) {
    mmu.write_8bit(register_.get(), cpu.A.get());

}

void Loads8bit::load_a16_a() {
    uint16_t address = cpu.fetch2bytes();
    mmu.write_16bit(address, cpu.A.get());
}

void Loads8bit::load_a_c() {
    uint16_t address = 0xFF00 + cpu.C.get();
    cpu.A.set(mmu.read_8bit(address));
}

void Loads8bit::load_c_a() {
    uint16_t address = 0xFF00 + cpu.C.get();
    mmu.write_8bit(address, cpu.A.get());
}

void Loads8bit::ld_a_hl_decrement() {
    cpu.A.set(cpu.HL->getAddressValue());
    cpu.HL->decrement();
}

void Loads8bit::ld_hl_a_decrement() {
    cpu.HL->setAddressValue(cpu.A.get());
    cpu.HL->decrement();
}

void Loads8bit::ld_a_hl_increment() {
    cpu.A.set(cpu.HL->getAddressValue());
    cpu.HL->increment();
}

void Loads8bit::ld_hl_a_increment() {
    cpu.HL->setAddressValue(cpu.A.get());
    cpu.HL->increment();
}

void Loads8bit::ldh_n_a() {
    uint16_t address = 0xFF + cpu.fetchByte();    
    mmu.write_8bit(address, cpu.A.get());
}

void Loads8bit::ldh_a_n() {
    uint16_t address = 0xFF + cpu.fetchByte();    
    cpu.A.set(mmu.read_8bit(address));
}


void Loads8bit::ld_r16_n16(RegisterPair register_) {
    register_.set(cpu.fetch2bytes());
}

void Loads8bit::ld_sp_hl() {
    cpu.SP.set(cpu.HL->get());
}

void Loads8bit::ld_hl_sp_n() {
    int8_t value = cpu.fetchSignedByte();
    int result = static_cast<int>(cpu.SP.get() + value);

    cpu.flags->set_z(0);
    cpu.flags->set_n(0);
    cpu.flags->set_h(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    cpu.flags->set_c(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    hl.set(static_cast<uint16_t>(result));
}

void Loads8bit::ld_n16_sp() {
    mmu.write_16bit(cpu.fetch2bytes(), cpu.SP.get());
}

void Loads8bit::push_r16(RegisterPair register_) {
    cpu.push_onto_stack(register_.getHigh());
    cpu.push_onto_stack(register_.getLow());
}

void Loads8bit::pop_r16(RegisterPair register_) {
    uint8_t low = cpu.pop_from_stack();
    uint8_t high = cpu.pop_from_stack();

    register_.setLow(low);
    register_.setHigh(high);
}