#define FMT_HEADER_ONLY

#include <stdexcept>
#include <iostream>
#include <string>

#include "spdlog/spdlog.h"

#include "control_unit.hpp"
#include "cpu.hpp"

uint16_t ControlUnit::fetch()
{
    uint16_t opcode = cpu.fetchByte();

    if (opcode == _2_BYTE_OPCODE_PREFIX)
    {
        opcode = (_2_BYTE_OPCODE_PREFIX << 8) | cpu.fetchByte();
    }

    return opcode;
}

uint8_t ControlUnit::execute()
{
    uint16_t pc = cpu.PC.get();
    uint16_t opcode = fetch();
    uint8_t cycles;

    spdlog::info("Opcode 0x{0:x}", opcode);
    spdlog::info("PC 0x{0:x}", pc);
    spdlog::info("AF 0x{0:x}", cpu.AF->get());
    spdlog::info("BC 0x{0:x}", cpu.BC->get());
    spdlog::info("DE 0x{0:x}", cpu.DE->get());
    spdlog::info("HL 0x{0:x}", cpu.HL->get());
    spdlog::info("SP 0x{0:x}", cpu.SP.get());
    spdlog::info("Z {}", cpu.flags->get_z());
    spdlog::info("N {}", cpu.flags->get_n());
    spdlog::info("H {}", cpu.flags->get_h());
    spdlog::info("C {}", cpu.flags->get_c());
    spdlog::info("IME {}", cpu.areInterruptsEnabled());


    /*
    std::cout << "Fetched opcode 0x" << std::hex << opcode << "\n";
    std::cout << "AF 0x" << std::hex << cpu.AF->get() << "\n";
    std::cout << "BC 0x" << std::hex << cpu.BC->get() << "\n";
    std::cout << "DE 0x" << std::hex << cpu.DE->get() << "\n";
    std::cout << "HL 0x" << std::hex << cpu.HL->get() << "\n";
    std::cout << "SP 0x" << std::hex << cpu.SP.get() << "\n";
    std::cout << "#########################################\n";
    */

    switch (opcode)
    {
    case 0x00:
        cycles = cpu.miscControl->nop();
        break;
    case 0x01:
        cycles = cpu.loads8bit->ld_r16_n16(*cpu.BC);
        break;
    case 0x02:
        cycles = cpu.loads8bit->load_r16_a(*cpu.BC);
        break;
    case 0x03:
        cycles = cpu.alu16bit->inc_r16(*cpu.BC);
        break;
    case 0x04:
        cycles = cpu.alu8bit->inc_r8(cpu.B);
        break;
    case 0x05:
        cycles = cpu.alu8bit->dec_r8(cpu.B);
        break;
    case 0x06:
        cycles = cpu.loads8bit->load_r8_n8(cpu.B);
        break;
    case 0x07:
        cycles = cpu.rotates->rlca();
        break;
    case 0x08:
        cycles = cpu.loads8bit->ld_n16_sp();
        break;
    case 0x09:
        cycles = cpu.alu16bit->add_hl_r16(*cpu.BC);
        break;
    case 0x0A:
        cycles = cpu.loads8bit->load_a_r16(*cpu.BC);
        break;
    case 0x0B:
        cycles = cpu.alu16bit->dec_r16(*cpu.BC);
        break;
    case 0x0C:
        cycles = cpu.alu8bit->inc_r8(cpu.C);
        break;
    case 0x0D:
        cycles = cpu.alu8bit->dec_r8(cpu.C);
        break;
    case 0x0E:
        cycles = cpu.loads8bit->load_r8_n8(cpu.C);
        break;
    case 0x0F:
        cycles = cpu.rotates->rrca();
        break;

    case 0x10:
        // 2-byte opcode whose second byte is ignored...
        cycles = cpu.miscControl->stop();
        break;
    case 0x11:
        cycles = cpu.loads8bit->ld_r16_n16(*cpu.DE);
        break;
    case 0x12:
        cycles = cpu.loads8bit->load_r16_a(*cpu.DE);
        break;
    case 0x13:
        cycles = cpu.alu16bit->inc_r16(*cpu.DE);
        break;
    case 0x14:
        cycles = cpu.alu8bit->inc_r8(cpu.D);
        break;
    case 0x15:
        cycles = cpu.alu8bit->dec_r8(cpu.D);
        break;
    case 0x16:
        cycles = cpu.loads8bit->load_r8_n8(cpu.D);
        break;
    case 0x17:
        cycles = cpu.rotates->rla();
        break;
    case 0x18:
        // TODO FIXME 8 or 12 cycles? Contradictory info
        cycles = cpu.jumps->jr_n();
        break;
    case 0x19:
        cycles = cpu.alu16bit->add_hl_r16(*cpu.DE);
        break;
    case 0x1A:
        cycles = cpu.loads8bit->load_a_r16(*cpu.DE);
        break;
    case 0x1B:
        cycles = cpu.alu16bit->dec_r16(*cpu.DE);
        break;
    case 0x1C:
        cycles = cpu.alu8bit->inc_r8(cpu.E);
        break;
    case 0x1D:
        cycles = cpu.alu8bit->dec_r8(cpu.E);
        break;
    case 0x1E:
        cycles = cpu.loads8bit->load_r8_n8(cpu.E);
        break;
    case 0x1F:
        cycles = cpu.rotates->rra();
        break;

    case 0x20:
        cycles = cpu.jumps->jr_cc_nn(Condition::NZ);
        break;
    case 0x21:
        cycles = cpu.loads8bit->ld_r16_n16(*cpu.HL);
        break;
    case 0x22:
        cycles = cpu.loads8bit->ld_hl_a_increment();
        break;
    case 0x23:
        cycles = cpu.alu16bit->inc_r16(*cpu.HL);
        break;
    case 0x24:
        cycles = cpu.alu8bit->inc_r8(cpu.H);
        break;
    case 0x25:
        cycles = cpu.alu8bit->dec_r8(cpu.H);
        break;
    case 0x26:
        cycles = cpu.loads8bit->load_r8_n8(cpu.H);
        break;
    case 0x27:
        cycles = cpu.alu8bit->daa();
        break;
    case 0x28:
        cycles = cpu.jumps->jr_cc_nn(Condition::Z);
        break;
    case 0x29:
        cycles = cpu.alu16bit->add_hl_r16(*cpu.HL);
        break;
    case 0x2A:
        cycles = cpu.loads8bit->ld_a_hl_increment();
        break;
    case 0x2B:
        cycles = cpu.alu16bit->dec_r16(*cpu.HL);
        break;
    case 0x2C:
        cycles = cpu.alu8bit->inc_r8(cpu.L);
        break;
    case 0x2D:
        cycles = cpu.alu8bit->dec_r8(cpu.L);
        break;
    case 0x2E:
        cycles = cpu.loads8bit->load_r8_n8(cpu.L);
        break;
    case 0x2F:
        cycles = cpu.alu8bit->cpl();
        break;

    case 0x30:
        cycles = cpu.jumps->jr_cc_nn(Condition::NC);
        break;
    case 0x31:
        cycles = cpu.loads8bit->ld_sp_n16();
        break;
    case 0x32:
        cycles = cpu.loads8bit->ld_hl_a_decrement();
        break;
    case 0x33:
        cycles = cpu.alu16bit->inc_sp();
        break;
    case 0x34:
        cycles = cpu.alu8bit->inc_hl();
        break;
    case 0x35:
        cycles = cpu.alu8bit->dec_hl();
        break;
    case 0x36:
        cycles = cpu.loads8bit->load_hl_d8();
        break;
    case 0x37:
        cycles = cpu.alu8bit->scf();
        break;
    case 0x38:
        cycles = cpu.jumps->jr_cc_nn(Condition::C);
        break;
    case 0x39:
        cycles = cpu.alu16bit->add_hl_sp();
        break;
    case 0x3A:
        cycles = cpu.loads8bit->ld_a_hl_increment();
        break;
    case 0x3B:
        cycles = cpu.alu16bit->dec_sp();
        break;
    case 0x3C:
        cycles = cpu.alu8bit->inc_r8(cpu.A);
        break;
    case 0x3D:
        cycles = cpu.alu8bit->dec_r8(cpu.A);
        break;
    case 0x3E:
        cycles = cpu.loads8bit->load_r8_n8(cpu.A);
        break;
    case 0x3F:
        cycles = cpu.alu8bit->ccf();
        break;

    case 0x40:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.B);
        break;
    case 0x41:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.C);
        break;
    case 0x42:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.D);
        break;
    case 0x43:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.E);
        break;
    case 0x44:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.H);
        break;
    case 0x45:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.L);
        break;
    case 0x46:
        cycles = cpu.loads8bit->load_r8_hl(cpu.B);
        break;
    case 0x47:
        cycles = cpu.loads8bit->load_r8_r8(cpu.B, cpu.A);
        break;
    case 0x48:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.B);
        break;
    case 0x49:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.C);
        break;
    case 0x4A:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.D);
        break;
    case 0x4B:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.E);
        break;
    case 0x4C:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.H);
        break;
    case 0x4D:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.L);
        break;
    case 0x4E:
        cycles = cpu.loads8bit->load_r8_hl(cpu.C);
        break;
    case 0x4F:
        cycles = cpu.loads8bit->load_r8_r8(cpu.C, cpu.A);
        break;

    case 0x50:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.B);
        break;
    case 0x51:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.C);
        break;
    case 0x52:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.D);
        break;
    case 0x53:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.E);
        break;
    case 0x54:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.H);
        break;
    case 0x55:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.L);
        break;
    case 0x56:
        cycles = cpu.loads8bit->load_r8_hl(cpu.D);
        break;
    case 0x57:
        cycles = cpu.loads8bit->load_r8_r8(cpu.D, cpu.A);
        break;
    case 0x58:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.B);
        break;
    case 0x59:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.C);
        break;
    case 0x5A:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.D);
        break;
    case 0x5B:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.E);
        break;
    case 0x5C:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.H);
        break;
    case 0x5D:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.L);
        break;
    case 0x5E:
        cycles = cpu.loads8bit->load_r8_hl(cpu.E);
        break;
    case 0x5F:
        cycles = cpu.loads8bit->load_r8_r8(cpu.E, cpu.A);
        break;

    case 0x60:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.B);
        break;
    case 0x61:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.C);
        break;
    case 0x62:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.D);
        break;
    case 0x63:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.E);
        break;
    case 0x64:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.H);
        break;
    case 0x65:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.L);
        break;
    case 0x66:
        cycles = cpu.loads8bit->load_r8_hl(cpu.H);
        break;
    case 0x67:
        cycles = cpu.loads8bit->load_r8_r8(cpu.H, cpu.A);
        break;
    case 0x68:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.B);
        break;
    case 0x69:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.C);
        break;
    case 0x6A:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.D);
        break;
    case 0x6B:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.E);
        break;
    case 0x6C:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.H);
        break;
    case 0x6D:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.L);
        break;
    case 0x6E:
        cycles = cpu.loads8bit->load_r8_hl(cpu.L);
        break;
    case 0x6F:
        cycles = cpu.loads8bit->load_r8_r8(cpu.L, cpu.A);
        break;

    case 0x70:
        cycles = cpu.loads8bit->load_hl_r8(cpu.B);
        break;
    case 0x71:
        cycles = cpu.loads8bit->load_hl_r8(cpu.C);
        break;
    case 0x72:
        cycles = cpu.loads8bit->load_hl_r8(cpu.D);
        break;
    case 0x73:
        cycles = cpu.loads8bit->load_hl_r8(cpu.E);
        break;
    case 0x74:
        cycles = cpu.loads8bit->load_hl_r8(cpu.H);
        break;
    case 0x75:
        cycles = cpu.loads8bit->load_hl_r8(cpu.L);
        break;
    case 0x76:
        cycles = cpu.miscControl->halt();
        break;
    case 0x77:
        cycles = cpu.loads8bit->load_hl_r8(cpu.A);
        break;
    case 0x78:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.B);
        break;
    case 0x79:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.C);
        break;
    case 0x7A:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.D);
        break;
    case 0x7B:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.E);
        break;
    case 0x7C:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.H);
        break;
    case 0x7D:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.L);
        break;
    case 0x7E:
        cycles = cpu.loads8bit->load_r8_hl(cpu.A);
        break;
    case 0x7F:
        cycles = cpu.loads8bit->load_r8_r8(cpu.A, cpu.A);
        break;

    case 0x80:
        cycles = cpu.alu8bit->add_a_r8(cpu.B);
        break;
    case 0x81:
        cycles = cpu.alu8bit->add_a_r8(cpu.C);
        break;
    case 0x82:
        cycles = cpu.alu8bit->add_a_r8(cpu.D);
        break;
    case 0x83:
        cycles = cpu.alu8bit->add_a_r8(cpu.E);
        break;
    case 0x84:
        cycles = cpu.alu8bit->add_a_r8(cpu.H);
        break;
    case 0x85:
        cycles = cpu.alu8bit->add_a_r8(cpu.L);
        break;
    case 0x86:
        cycles = cpu.alu8bit->add_a_hl();
        break;
    case 0x87:
        cycles = cpu.alu8bit->add_a_r8(cpu.A);
        break;
    case 0x88:
        cycles = cpu.alu8bit->adc_a_r8(cpu.B);
        break;
    case 0x89:
        cycles = cpu.alu8bit->adc_a_r8(cpu.C);
        break;
    case 0x8A:
        cycles = cpu.alu8bit->adc_a_r8(cpu.D);
        break;
    case 0x8B:
        cycles = cpu.alu8bit->adc_a_r8(cpu.E);
        break;
    case 0x8C:
        cycles = cpu.alu8bit->adc_a_r8(cpu.H);
        break;
    case 0x8D:
        cycles = cpu.alu8bit->adc_a_r8(cpu.L);
        break;
    case 0x8E:
        cycles = cpu.alu8bit->adc_a_hl();
        break;
    case 0x8F:
        cycles = cpu.alu8bit->adc_a_r8(cpu.A);
        break;

    case 0x90:
        cycles = cpu.alu8bit->sub_a_r8(cpu.B);
        break;
    case 0x91:
        cycles = cpu.alu8bit->sub_a_r8(cpu.C);
        break;
    case 0x92:
        cycles = cpu.alu8bit->sub_a_r8(cpu.D);
        break;
    case 0x93:
        cycles = cpu.alu8bit->sub_a_r8(cpu.E);
        break;
    case 0x94:
        cycles = cpu.alu8bit->sub_a_r8(cpu.H);
        break;
    case 0x95:
        cycles = cpu.alu8bit->sub_a_r8(cpu.L);
        break;
    case 0x96:
        cycles = cpu.alu8bit->sub_a_hl();
        break;
    case 0x97:
        cycles = cpu.alu8bit->sub_a_r8(cpu.A);
        break;
    case 0x98:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.B);
        break;
    case 0x99:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.C);
        break;
    case 0x9A:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.D);
        break;
    case 0x9B:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.E);
        break;
    case 0x9C:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.H);
        break;
    case 0x9D:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.L);
        break;
    case 0x9E:
        cycles = cpu.alu8bit->sbc_a_hl();
        break;
    case 0x9F:
        cycles = cpu.alu8bit->sbc_a_r8(cpu.A);
        break;

    case 0xA0:
        cycles = cpu.alu8bit->and_a_r8(cpu.B);
        break;
    case 0xA1:
        cycles = cpu.alu8bit->and_a_r8(cpu.C);
        break;
    case 0xA2:
        cycles = cpu.alu8bit->and_a_r8(cpu.D);
        break;
    case 0xA3:
        cycles = cpu.alu8bit->and_a_r8(cpu.E);
        break;
    case 0xA4:
        cycles = cpu.alu8bit->and_a_r8(cpu.H);
        break;
    case 0xA5:
        cycles = cpu.alu8bit->and_a_r8(cpu.L);
        break;
    case 0xA6:
        cycles = cpu.alu8bit->and_a_hl();
        break;
    case 0xA7:
        cycles = cpu.alu8bit->and_a_r8(cpu.A);
        break;
    case 0xA8:
        cycles = cpu.alu8bit->xor_a_r8(cpu.B);
        break;
    case 0xA9:
        cycles = cpu.alu8bit->xor_a_r8(cpu.C);
        break;
    case 0xAA:
        cycles = cpu.alu8bit->xor_a_r8(cpu.D);
        break;
    case 0xAB:
        cycles = cpu.alu8bit->xor_a_r8(cpu.E);
        break;
    case 0xAC:
        cycles = cpu.alu8bit->xor_a_r8(cpu.H);
        break;
    case 0xAD:
        cycles = cpu.alu8bit->xor_a_r8(cpu.L);
        break;
    case 0xAE:
        cycles = cpu.alu8bit->xor_a_hl();
        break;
    case 0xAF:
        cycles = cpu.alu8bit->xor_a_r8(cpu.A);
        break;

    case 0xB0:
        cycles = cpu.alu8bit->or_a_r8(cpu.B);
        break;
    case 0xB1:
        cycles = cpu.alu8bit->or_a_r8(cpu.C);
        break;
    case 0xB2:
        cycles = cpu.alu8bit->or_a_r8(cpu.D);
        break;
    case 0xB3:
        cycles = cpu.alu8bit->or_a_r8(cpu.E);
        break;
    case 0xB4:
        cycles = cpu.alu8bit->or_a_r8(cpu.H);
        break;
    case 0xB5:
        cycles = cpu.alu8bit->or_a_r8(cpu.L);
        break;
    case 0xB6:
        cycles = cpu.alu8bit->or_a_hl();
        break;
    case 0xB7:
        cycles = cpu.alu8bit->or_a_r8(cpu.A);
        break;
    case 0xB8:
        cycles = cpu.alu8bit->cp_a_r8(cpu.B);
        break;
    case 0xB9:
        cycles = cpu.alu8bit->cp_a_r8(cpu.C);
        break;
    case 0xBA:
        cycles = cpu.alu8bit->cp_a_r8(cpu.D);
        break;
    case 0xBB:
        cycles = cpu.alu8bit->cp_a_r8(cpu.E);
        break;
    case 0xBC:
        cycles = cpu.alu8bit->cp_a_r8(cpu.H);
        break;
    case 0xBD:
        cycles = cpu.alu8bit->cp_a_r8(cpu.L);
        break;
    case 0xBE:
        cycles = cpu.alu8bit->cp_a_hl();
        break;
    case 0xBF:
        cycles = cpu.alu8bit->cp_a_r8(cpu.A);
        break;

    case 0xC0:
        cycles = cpu.jumps->ret_cc(Condition::NZ);
        break;
    case 0xC1:
        cycles = cpu.loads8bit->pop_r16(*cpu.BC);
        break;
    case 0xC2:
        cycles = cpu.jumps->jp_cc_nn(Condition::NZ);
        break;
    case 0xC3:
        cycles = cpu.jumps->jp_nn();
        break;
    case 0xC4:
        cycles = cpu.jumps->call_cc_nn(Condition::NZ);
        break;
    case 0xC5:
        cycles = cpu.loads8bit->push_r16(*cpu.BC);
        break;
    case 0xC6:
        cycles = cpu.alu8bit->add_a_n8();
        break;
    case 0xC7:
        cycles = cpu.jumps->rst(0);
        break;
    case 0xC8:
        cycles = cpu.jumps->ret_cc(Condition::Z);
        break;
    case 0xC9:
        cycles = cpu.jumps->ret();
        break;
    case 0xCA:
        cycles = cpu.jumps->jp_cc_nn(Condition::Z);
        break;
    case 0xCC:
        cycles = cpu.jumps->call_cc_nn(Condition::Z);
        break;
    case 0xCD:
        cycles = cpu.jumps->call_nn();
        break;
    case 0xCE:
        cycles = cpu.alu8bit->adc_a_n8();
        break;
    case 0xCF:
        cycles = cpu.jumps->rst(0x08);
        break;

    case 0xD0:
        cycles = cpu.jumps->ret_cc(Condition::NC);
        break;
    case 0xD1:
        cycles = cpu.loads8bit->pop_r16(*cpu.DE);
        break;
    case 0xD2:
        cycles = cpu.jumps->jp_cc_nn(Condition::NC);
        break;
    case 0xD4:
        cycles = cpu.jumps->call_cc_nn(Condition::NC);
        break;
    case 0xD5:
        cycles = cpu.loads8bit->push_r16(*cpu.DE);
        break;
    case 0xD6:
        cycles = cpu.alu8bit->sub_a_n8();
        break;
    case 0xD7:
        cycles = cpu.jumps->rst(0x10);
        break;
    case 0xD8:
        cycles = cpu.jumps->ret_cc(Condition::C);
        break;
    case 0xD9:
        cycles = cpu.jumps->reti();
        break;
    case 0xDA:
        cycles = cpu.jumps->jp_cc_nn(Condition::C);
        break;
    case 0xDC:
        cycles = cpu.jumps->call_cc_nn(Condition::C);
        break;
    case 0xDE:
        cycles = cpu.alu8bit->sbc_a_n8();
        break;
    case 0xDF:
        cycles = cpu.jumps->rst(0x18);

    case 0xE0:
        cycles = cpu.loads8bit->ldh_n_a();
        break;
    case 0xE1:
        cycles = cpu.loads8bit->pop_r16(*cpu.HL);
        break;
    case 0xE2:
        cycles = cpu.loads8bit->ld_c_a();
        break;
    case 0xE5:
        cycles = cpu.loads8bit->push_r16(*cpu.HL);
        break;
    case 0xE6:
        cycles = cpu.alu8bit->and_a_n8();
        break;
    case 0xE7:
        cycles = cpu.jumps->rst(0x20);
        break;
    case 0xE8:
        cycles = cpu.alu16bit->add_sp_s8();
        break;
    case 0xE9:
        cycles = cpu.jumps->jp_hl();
        break;
    case 0xEA:
        cycles = cpu.loads8bit->load_a16_a();
        break;
    case 0xEE:
        cycles = cpu.alu8bit->xor_a_n8();
        break;
    case 0xEF:
        cycles = cpu.jumps->rst(0x28);

    case 0xF0:
        cycles = cpu.loads8bit->ldh_a_n();
        break;
    case 0xF1:
        cycles = cpu.loads8bit->pop_af();
        break;
    case 0xF2:
        cycles = cpu.loads8bit->ld_a_c();
        break;
    case 0xF3:
        cycles = cpu.miscControl->di();
        break;
    case 0xF5:
        cycles = cpu.loads8bit->push_r16(*cpu.AF);
        break;
    case 0xF6:
        cycles = cpu.alu8bit->or_a_n8();
        break;
    case 0xF7:
        cycles = cpu.jumps->rst(0x30);
        break;
    case 0xF8:
        cycles = cpu.loads8bit->ld_hl_sp_n();
        break;
    case 0xF9:
        cycles = cpu.loads8bit->ld_sp_hl();
        break;
    case 0xFA:
        cycles = cpu.loads8bit->load_a_address();
        break;
    case 0xFB:
        cycles = cpu.miscControl->ei();
        break;
    case 0xFE:
        cycles = cpu.alu8bit->cp_a_n8();
        break;
    case 0xFF:
        cycles = cpu.jumps->rst(0x38);
        break;

    case 0xCB00:
        cycles = cpu.rotates->rlc_r8(cpu.B);
        break;
    case 0xCB01:
        cycles = cpu.rotates->rlc_r8(cpu.C);
        break;
    case 0xCB02:
        cycles = cpu.rotates->rlc_r8(cpu.D);
        break;
    case 0xCB03:
        cycles = cpu.rotates->rlc_r8(cpu.E);
        break;
    case 0xCB04:
        cycles = cpu.rotates->rlc_r8(cpu.H);
        break;
    case 0xCB05:
        cycles = cpu.rotates->rlc_r8(cpu.L);
        break;
    case 0xCB06:
        cycles = cpu.rotates->rlc_hl();
        break;
    case 0xCB07:
        cycles = cpu.rotates->rlc_r8(cpu.A);
        break;

    case 0xCB08:
        cycles = cpu.rotates->rrc_r8(cpu.B);
        break;
    case 0xCB09:
        cycles = cpu.rotates->rrc_r8(cpu.C);
        break;
    case 0xCB0A:
        cycles = cpu.rotates->rrc_r8(cpu.D);
        break;
    case 0xCB0B:
        cycles = cpu.rotates->rrc_r8(cpu.E);
        break;
    case 0xCB0C:
        cycles = cpu.rotates->rrc_r8(cpu.H);
        break;
    case 0xCB0D:
        cycles = cpu.rotates->rrc_r8(cpu.L);
        break;
    case 0xCB0E:
        cycles = cpu.rotates->rrc_hl();
        break;
    case 0xCB0F:
        cycles = cpu.rotates->rrc_r8(cpu.A);
        break;

    case 0xCB10:
        cycles = cpu.rotates->rl_r8(cpu.B);
        break;
    case 0xCB11:
        cycles = cpu.rotates->rl_r8(cpu.C);
        break;
    case 0xCB12:
        cycles = cpu.rotates->rl_r8(cpu.D);
        break;
    case 0xCB13:
        cycles = cpu.rotates->rl_r8(cpu.E);
        break;
    case 0xCB14:
        cycles = cpu.rotates->rl_r8(cpu.H);
        break;
    case 0xCB15:
        cycles = cpu.rotates->rl_r8(cpu.L);
        break;
    case 0xCB16:
        cycles = cpu.rotates->rl_hl();
        break;
    case 0xCB17:
        cycles = cpu.rotates->rl_r8(cpu.A);
        break;

    case 0xCB18:
        cycles = cpu.rotates->rr_r8(cpu.B);
        break;
    case 0xCB19:
        cycles = cpu.rotates->rr_r8(cpu.C);
        break;
    case 0xCB1A:
        cycles = cpu.rotates->rr_r8(cpu.D);
        break;
    case 0xCB1B:
        cycles = cpu.rotates->rr_r8(cpu.E);
        break;
    case 0xCB1C:
        cycles = cpu.rotates->rr_r8(cpu.H);
        break;
    case 0xCB1D:
        cycles = cpu.rotates->rr_r8(cpu.L);
        break;
    case 0xCB1E:
        cycles = cpu.rotates->rr_hl();
        break;
    case 0xCB1F:
        cycles = cpu.rotates->rr_r8(cpu.A);
        break;

    case 0xCB20:
        cycles = cpu.rotates->sla_r8(cpu.B);
        break;
    case 0xCB21:
        cycles = cpu.rotates->sla_r8(cpu.C);
        break;
    case 0xCB22:
        cycles = cpu.rotates->sla_r8(cpu.D);
        break;
    case 0xCB23:
        cycles = cpu.rotates->sla_r8(cpu.E);
        break;
    case 0xCB24:
        cycles = cpu.rotates->sla_r8(cpu.H);
        break;
    case 0xCB25:
        cycles = cpu.rotates->sla_r8(cpu.L);
        break;
    case 0xCB26:
        cycles = cpu.rotates->sla_hl();
        break;
    case 0xCB27:
        cycles = cpu.rotates->sla_r8(cpu.A);
        break;

    case 0xCB28:
        cycles = cpu.rotates->sra_r8(cpu.B);
        break;
    case 0xCB29:
        cycles = cpu.rotates->sra_r8(cpu.C);
        break;
    case 0xCB2A:
        cycles = cpu.rotates->sra_r8(cpu.D);
        break;
    case 0xCB2B:
        cycles = cpu.rotates->sra_r8(cpu.E);
        break;
    case 0xCB2C:
        cycles = cpu.rotates->sra_r8(cpu.H);
        break;
    case 0xCB2D:
        cycles = cpu.rotates->sra_r8(cpu.L);
        break;
    case 0xCB2E:
        cycles = cpu.rotates->sra_hl();
        break;
    case 0xCB2F:
        cycles = cpu.rotates->sra_r8(cpu.A);
        break;

    case 0xCB30:
        cycles = cpu.rotates->swap_r8(cpu.B);
        break;
    case 0xCB31:
        cycles = cpu.rotates->swap_r8(cpu.C);
        break;
    case 0xCB32:
        cycles = cpu.rotates->swap_r8(cpu.D);
        break;
    case 0xCB33:
        cycles = cpu.rotates->swap_r8(cpu.E);
        break;
    case 0xCB34:
        cycles = cpu.rotates->swap_r8(cpu.H);
        break;
    case 0xCB35:
        cycles = cpu.rotates->swap_r8(cpu.L);
        break;
    case 0xCB36:
        cycles = cpu.rotates->swap_hl();
        break;
    case 0xCB37:
        cycles = cpu.rotates->swap_r8(cpu.A);
        break;

    case 0xCB38:
        cycles = cpu.rotates->srl_r8(cpu.B);
        break;
    case 0xCB39:
        cycles = cpu.rotates->srl_r8(cpu.C);
        break;
    case 0xCB3A:
        cycles = cpu.rotates->srl_r8(cpu.D);
        break;
    case 0xCB3B:
        cycles = cpu.rotates->srl_r8(cpu.E);
        break;
    case 0xCB3C:
        cycles = cpu.rotates->srl_r8(cpu.H);
        break;
    case 0xCB3D:
        cycles = cpu.rotates->srl_r8(cpu.L);
        break;
    case 0xCB3E:
        cycles = cpu.rotates->srl_hl();
        break;
    case 0xCB3F:
        cycles = cpu.rotates->srl_r8(cpu.A);
        break;

    case 0xCB40:
        cycles = cpu.bit->bit(cpu.B, 0);
        break;
    case 0xCB41:
        cycles = cpu.bit->bit(cpu.C, 0);
        break;
    case 0xCB42:
        cycles = cpu.bit->bit(cpu.D, 0);
        break;
    case 0xCB43:
        cycles = cpu.bit->bit(cpu.E, 0);
        break;
    case 0xCB44:
        cycles = cpu.bit->bit(cpu.H, 0);
        break;
    case 0xCB45:
        cycles = cpu.bit->bit(cpu.L, 0);
        break;
    case 0xCB46:
        cycles = cpu.bit->bit_hl(0);
        break;
    case 0xCB47:
        cycles = cpu.bit->bit(cpu.A, 0);
        break;

    case 0xCB48:
        cycles = cpu.bit->bit(cpu.B, 1);
        break;
    case 0xCB49:
        cycles = cpu.bit->bit(cpu.C, 1);
        break;
    case 0xCB4A:
        cycles = cpu.bit->bit(cpu.D, 1);
        break;
    case 0xCB4B:
        cycles = cpu.bit->bit(cpu.E, 1);
        break;
    case 0xCB4C:
        cycles = cpu.bit->bit(cpu.H, 1);
        break;
    case 0xCB4D:
        cycles = cpu.bit->bit(cpu.L, 1);
        break;
    case 0xCB4E:
        cycles = cpu.bit->bit_hl(1);
        break;
    case 0xCB4F:
        cycles = cpu.bit->bit(cpu.A, 1);
        break;

    case 0xCB50:
        cycles = cpu.bit->bit(cpu.B, 2);
        break;
    case 0xCB51:
        cycles = cpu.bit->bit(cpu.C, 2);
        break;
    case 0xCB52:
        cycles = cpu.bit->bit(cpu.D, 2);
        break;
    case 0xCB53:
        cycles = cpu.bit->bit(cpu.E, 2);
        break;
    case 0xCB54:
        cycles = cpu.bit->bit(cpu.H, 2);
        break;
    case 0xCB55:
        cycles = cpu.bit->bit(cpu.L, 2);
        break;
    case 0xCB56:
        cycles = cpu.bit->bit_hl(2);
        break;
    case 0xCB57:
        cycles = cpu.bit->bit(cpu.A, 2);
        break;

    case 0xCB58:
        cycles = cpu.bit->bit(cpu.B, 3);
        break;
    case 0xCB59:
        cycles = cpu.bit->bit(cpu.C, 3);
        break;
    case 0xCB5A:
        cycles = cpu.bit->bit(cpu.D, 3);
        break;
    case 0xCB5B:
        cycles = cpu.bit->bit(cpu.E, 3);
        break;
    case 0xCB5C:
        cycles = cpu.bit->bit(cpu.H, 3);
        break;
    case 0xCB5D:
        cycles = cpu.bit->bit(cpu.L, 3);
        break;
    case 0xCB5E:
        cycles = cpu.bit->bit_hl(3);
        break;
    case 0xCB5F:
        cycles = cpu.bit->bit(cpu.A, 3);
        break;

    case 0xCB60:
        cycles = cpu.bit->bit(cpu.B, 4);
        break;
    case 0xCB61:
        cycles = cpu.bit->bit(cpu.C, 4);
        break;
    case 0xCB62:
        cycles = cpu.bit->bit(cpu.D, 4);
        break;
    case 0xCB63:
        cycles = cpu.bit->bit(cpu.E, 4);
        break;
    case 0xCB64:
        cycles = cpu.bit->bit(cpu.H, 4);
        break;
    case 0xCB65:
        cycles = cpu.bit->bit(cpu.L, 4);
        break;
    case 0xCB66:
        cycles = cpu.bit->bit_hl(4);
        break;
    case 0xCB67:
        cycles = cpu.bit->bit(cpu.A, 4);
        break;

    case 0xCB68:
        cycles = cpu.bit->bit(cpu.B, 5);
        break;
    case 0xCB69:
        cycles = cpu.bit->bit(cpu.C, 5);
        break;
    case 0xCB6A:
        cycles = cpu.bit->bit(cpu.D, 5);
        break;
    case 0xCB6B:
        cycles = cpu.bit->bit(cpu.E, 5);
        break;
    case 0xCB6C:
        cycles = cpu.bit->bit(cpu.H, 5);
        break;
    case 0xCB6D:
        cycles = cpu.bit->bit(cpu.L, 5);
        break;
    case 0xCB6E:
        cycles = cpu.bit->bit_hl(5);
        break;
    case 0xCB6F:
        cycles = cpu.bit->bit(cpu.A, 5);
        break;

    case 0xCB70:
        cycles = cpu.bit->bit(cpu.B, 6);
        break;
    case 0xCB71:
        cycles = cpu.bit->bit(cpu.C, 6);
        break;
    case 0xCB72:
        cycles = cpu.bit->bit(cpu.D, 6);
        break;
    case 0xCB73:
        cycles = cpu.bit->bit(cpu.E, 6);
        break;
    case 0xCB74:
        cycles = cpu.bit->bit(cpu.H, 6);
        break;
    case 0xCB75:
        cycles = cpu.bit->bit(cpu.L, 6);
        break;
    case 0xCB76:
        cycles = cpu.bit->bit_hl(6);
        break;
    case 0xCB77:
        cycles = cpu.bit->bit(cpu.A, 6);
        break;

    case 0xCB78:
        cycles = cpu.bit->bit(cpu.B, 7);
        break;
    case 0xCB79:
        cycles = cpu.bit->bit(cpu.C, 7);
        break;
    case 0xCB7A:
        cycles = cpu.bit->bit(cpu.D, 7);
        break;
    case 0xCB7B:
        cycles = cpu.bit->bit(cpu.E, 7);
        break;
    case 0xCB7C:
        cycles = cpu.bit->bit(cpu.H, 7);
        break;
    case 0xCB7D:
        cycles = cpu.bit->bit(cpu.L, 7);
        break;
    case 0xCB7E:
        cycles = cpu.bit->bit_hl(7);
        break;
    case 0xCB7F:
        cycles = cpu.bit->bit(cpu.A, 7);
        break;

    case 0xCB80:
        cycles = cpu.bit->res(cpu.B, 0);
        break;
    case 0xCB81:
        cycles = cpu.bit->res(cpu.C, 0);
        break;
    case 0xCB82:
        cycles = cpu.bit->res(cpu.D, 0);
        break;
    case 0xCB83:
        cycles = cpu.bit->res(cpu.E, 0);
        break;
    case 0xCB84:
        cycles = cpu.bit->res(cpu.H, 0);
        break;
    case 0xCB85:
        cycles = cpu.bit->res(cpu.L, 0);
        break;
    case 0xCB86:
        cycles = cpu.bit->res_hl(0);
        break;
    case 0xCB87:
        cycles = cpu.bit->res(cpu.A, 0);
        break;

    case 0xCB88:
        cycles = cpu.bit->res(cpu.B, 1);
        break;
    case 0xCB89:
        cycles = cpu.bit->res(cpu.C, 1);
        break;
    case 0xCB8A:
        cycles = cpu.bit->res(cpu.D, 1);
        break;
    case 0xCB8B:
        cycles = cpu.bit->res(cpu.E, 1);
        break;
    case 0xCB8C:
        cycles = cpu.bit->res(cpu.H, 1);
        break;
    case 0xCB8D:
        cycles = cpu.bit->res(cpu.L, 1);
        break;
    case 0xCB8E:
        cycles = cpu.bit->res_hl(1);
        break;
    case 0xCB8F:
        cycles = cpu.bit->res(cpu.A, 1);
        break;

    case 0xCB90:
        cycles = cpu.bit->res(cpu.B, 2);
        break;
    case 0xCB91:
        cycles = cpu.bit->res(cpu.C, 2);
        break;
    case 0xCB92:
        cycles = cpu.bit->res(cpu.D, 2);
        break;
    case 0xCB93:
        cycles = cpu.bit->res(cpu.E, 2);
        break;
    case 0xCB94:
        cycles = cpu.bit->res(cpu.H, 2);
        break;
    case 0xCB95:
        cycles = cpu.bit->res(cpu.L, 2);
        break;
    case 0xCB96:
        cycles = cpu.bit->res_hl(2);
        break;
    case 0xCB97:
        cycles = cpu.bit->res(cpu.A, 2);
        break;

    case 0xCB98:
        cycles = cpu.bit->res(cpu.B, 3);
        break;
    case 0xCB99:
        cycles = cpu.bit->res(cpu.C, 3);
        break;
    case 0xCB9A:
        cycles = cpu.bit->res(cpu.D, 3);
        break;
    case 0xCB9B:
        cycles = cpu.bit->res(cpu.E, 3);
        break;
    case 0xCB9C:
        cycles = cpu.bit->res(cpu.H, 3);
        break;
    case 0xCB9D:
        cycles = cpu.bit->res(cpu.L, 3);
        break;
    case 0xCB9E:
        cycles = cpu.bit->res_hl(3);
        break;
    case 0xCB9F:
        cycles = cpu.bit->res(cpu.A, 3);
        break;

    case 0xCBA0:
        cycles = cpu.bit->res(cpu.B, 4);
        break;
    case 0xCBA1:
        cycles = cpu.bit->res(cpu.C, 4);
        break;
    case 0xCBA2:
        cycles = cpu.bit->res(cpu.D, 4);
        break;
    case 0xCBA3:
        cycles = cpu.bit->res(cpu.E, 4);
        break;
    case 0xCBA4:
        cycles = cpu.bit->res(cpu.H, 4);
        break;
    case 0xCBA5:
        cycles = cpu.bit->res(cpu.L, 4);
        break;
    case 0xCBA6:
        cycles = cpu.bit->res_hl(4);
        break;
    case 0xCBA7:
        cycles = cpu.bit->res(cpu.A, 4);
        break;

    case 0xCBA8:
        cycles = cpu.bit->res(cpu.B, 5);
        break;
    case 0xCBA9:
        cycles = cpu.bit->res(cpu.C, 5);
        break;
    case 0xCBAA:
        cycles = cpu.bit->res(cpu.D, 5);
        break;
    case 0xCBAB:
        cycles = cpu.bit->res(cpu.E, 5);
        break;
    case 0xCBAC:
        cycles = cpu.bit->res(cpu.H, 5);
        break;
    case 0xCBAD:
        cycles = cpu.bit->res(cpu.L, 5);
        break;
    case 0xCBAE:
        cycles = cpu.bit->res_hl(5);
        break;
    case 0xCBAF:
        cycles = cpu.bit->res(cpu.A, 5);
        break;

    case 0xCBB0:
        cycles = cpu.bit->res(cpu.B, 6);
        break;
    case 0xCBB1:
        cycles = cpu.bit->res(cpu.C, 6);
        break;
    case 0xCBB2:
        cycles = cpu.bit->res(cpu.D, 6);
        break;
    case 0xCBB3:
        cycles = cpu.bit->res(cpu.E, 6);
        break;
    case 0xCBB4:
        cycles = cpu.bit->res(cpu.H, 6);
        break;
    case 0xCBB5:
        cycles = cpu.bit->res(cpu.L, 6);
        break;
    case 0xCBB6:
        cycles = cpu.bit->res_hl(6);
        break;
    case 0xCBB7:
        cycles = cpu.bit->res(cpu.A, 6);
        break;

    case 0xCBB8:
        cycles = cpu.bit->res(cpu.B, 7);
        break;
    case 0xCBB9:
        cycles = cpu.bit->res(cpu.C, 7);
        break;
    case 0xCBBA:
        cycles = cpu.bit->res(cpu.D, 7);
        break;
    case 0xCBBB:
        cycles = cpu.bit->res(cpu.E, 7);
        break;
    case 0xCBBC:
        cycles = cpu.bit->res(cpu.H, 7);
        break;
    case 0xCBBD:
        cycles = cpu.bit->res(cpu.L, 7);
        break;
    case 0xCBBE:
        cycles = cpu.bit->res_hl(7);
        break;
    case 0xCBBF:
        cycles = cpu.bit->res(cpu.A, 7);
        break;

    case 0xCBC0:
        cycles = cpu.bit->set(cpu.B, 0);
        break;
    case 0xCBC1:
        cycles = cpu.bit->set(cpu.C, 0);
        break;
    case 0xCBC2:
        cycles = cpu.bit->set(cpu.D, 0);
        break;
    case 0xCBC3:
        cycles = cpu.bit->set(cpu.E, 0);
        break;
    case 0xCBC4:
        cycles = cpu.bit->set(cpu.H, 0);
        break;
    case 0xCBC5:
        cycles = cpu.bit->set(cpu.L, 0);
        break;
    case 0xCBC6:
        cycles = cpu.bit->set_hl(0);
        break;
    case 0xCBC7:
        cycles = cpu.bit->set(cpu.A, 0);
        break;

    case 0xCBC8:
        cycles = cpu.bit->set(cpu.B, 1);
        break;
    case 0xCBC9:
        cycles = cpu.bit->set(cpu.C, 1);
        break;
    case 0xCBCA:
        cycles = cpu.bit->set(cpu.D, 1);
        break;
    case 0xCBCB:
        cycles = cpu.bit->set(cpu.E, 1);
        break;
    case 0xCBCC:
        cycles = cpu.bit->set(cpu.H, 1);
        break;
    case 0xCBCD:
        cycles = cpu.bit->set(cpu.L, 1);
        break;
    case 0xCBCE:
        cycles = cpu.bit->set_hl(1);
        break;
    case 0xCBCF:
        cycles = cpu.bit->set(cpu.A, 1);
        break;

    case 0xCBD0:
        cycles = cpu.bit->set(cpu.B, 2);
        break;
    case 0xCBD1:
        cycles = cpu.bit->set(cpu.C, 2);
        break;
    case 0xCBD2:
        cycles = cpu.bit->set(cpu.D, 2);
        break;
    case 0xCBD3:
        cycles = cpu.bit->set(cpu.E, 2);
        break;
    case 0xCBD4:
        cycles = cpu.bit->set(cpu.H, 2);
        break;
    case 0xCBD5:
        cycles = cpu.bit->set(cpu.L, 2);
        break;
    case 0xCBD6:
        cycles = cpu.bit->set_hl(2);
        break;
    case 0xCBD7:
        cycles = cpu.bit->set(cpu.A, 2);
        break;

    case 0xCBD8:
        cycles = cpu.bit->set(cpu.B, 3);
        break;
    case 0xCBD9:
        cycles = cpu.bit->set(cpu.C, 3);
        break;
    case 0xCBDA:
        cycles = cpu.bit->set(cpu.D, 3);
        break;
    case 0xCBDB:
        cycles = cpu.bit->set(cpu.E, 3);
        break;
    case 0xCBDC:
        cycles = cpu.bit->set(cpu.H, 3);
        break;
    case 0xCBDD:
        cycles = cpu.bit->set(cpu.L, 3);
        break;
    case 0xCBDE:
        cycles = cpu.bit->set_hl(3);
        break;
    case 0xCBDF:
        cycles = cpu.bit->set(cpu.A, 3);
        break;

    case 0xCBE0:
        cycles = cpu.bit->set(cpu.B, 4);
        break;
    case 0xCBE1:
        cycles = cpu.bit->set(cpu.C, 4);
        break;
    case 0xCBE2:
        cycles = cpu.bit->set(cpu.D, 4);
        break;
    case 0xCBE3:
        cycles = cpu.bit->set(cpu.E, 4);
        break;
    case 0xCBE4:
        cycles = cpu.bit->set(cpu.H, 4);
        break;
    case 0xCBE5:
        cycles = cpu.bit->set(cpu.L, 4);
        break;
    case 0xCBE6:
        cycles = cpu.bit->set_hl(4);
        break;
    case 0xCBE7:
        cycles = cpu.bit->set(cpu.A, 4);
        break;

    case 0xCBE8:
        cycles = cpu.bit->set(cpu.B, 5);
        break;
    case 0xCBE9:
        cycles = cpu.bit->set(cpu.C, 5);
        break;
    case 0xCBEA:
        cycles = cpu.bit->set(cpu.D, 5);
        break;
    case 0xCBEB:
        cycles = cpu.bit->set(cpu.E, 5);
        break;
    case 0xCBEC:
        cycles = cpu.bit->set(cpu.H, 5);
        break;
    case 0xCBED:
        cycles = cpu.bit->set(cpu.L, 5);
        break;
    case 0xCBEE:
        cycles = cpu.bit->set_hl(5);
        break;
    case 0xCBEF:
        cycles = cpu.bit->set(cpu.A, 5);
        break;

    case 0xCBF0:
        cycles = cpu.bit->set(cpu.B, 6);
        break;
    case 0xCBF1:
        cycles = cpu.bit->set(cpu.C, 6);
        break;
    case 0xCBF2:
        cycles = cpu.bit->set(cpu.D, 6);
        break;
    case 0xCBF3:
        cycles = cpu.bit->set(cpu.E, 6);
        break;
    case 0xCBF4:
        cycles = cpu.bit->set(cpu.H, 6);
        break;
    case 0xCBF5:
        cycles = cpu.bit->set(cpu.L, 6);
        break;
    case 0xCBF6:
        cycles = cpu.bit->set_hl(6);
        break;
    case 0xCBF7:
        cycles = cpu.bit->set(cpu.A, 6);
        break;

    case 0xCBF8:
        cycles = cpu.bit->set(cpu.B, 7);
        break;
    case 0xCBF9:
        cycles = cpu.bit->set(cpu.C, 7);
        break;
    case 0xCBFA:
        cycles = cpu.bit->set(cpu.D, 7);
        break;
    case 0xCBFB:
        cycles = cpu.bit->set(cpu.E, 7);
        break;
    case 0xCBFC:
        cycles = cpu.bit->set(cpu.H, 7);
        break;
    case 0xCBFD:
        cycles = cpu.bit->set(cpu.L, 7);
        break;
    case 0xCBFE:
        cycles = cpu.bit->set_hl(7);
        break;
    case 0xCBFF:
        cycles = cpu.bit->set(cpu.A, 7);
        break;

    default:
        std::cout << "Illegal opcode " << std::hex << opcode << "\n";
        // throw std::runtime_error("");
        break;
    }

    return cycles;
}
