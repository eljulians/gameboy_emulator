#include <stdexcept>
#include <iostream>
#include <string>
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
    std::cout << "PC 0x" << std::hex << cpu.PC.get() << "\n";
    uint16_t opcode = fetch();
    uint8_t cycles;

    std::cout << "Fetched opcode 0x" << std::hex << opcode << "\n";
    std::cout << "AF 0x" << std::hex << cpu.AF->get() << "\n";
    std::cout << "BC 0x" << std::hex << cpu.BC->get() << "\n";
    std::cout << "DE 0x" << std::hex << cpu.DE->get() << "\n";
    std::cout << "HL 0x" << std::hex << cpu.HL->get() << "\n";
    std::cout << "SP 0x" << std::hex << cpu.SP.get() << "\n";
    std::cout << "#########################################\n";

    switch (opcode)
    {
    case 0x00:
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
        std::cout << "Operation STOP (0x10) not implemented\n";
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
        std::cout << "Operation DAA (0x27) not implemented\n";
        cycles = 4;
        //cycles = cpu.alu8bit.daa();
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
        std::cout << "Operation CPL (0x2F) not implemented\n";
        //cycles = cpu.alu8bit->cp_a_hl()
        cycles = 4;
        break;

    case 0x30:
        cycles = cpu.jumps->jr_cc_nn(Condition::NZ);
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
        cycles = cpu.loads8bit->load_r8_n8(cpu.H);
        break;
    case 0x37:
        std::cout << "Operation SCF (0x37) not implemented\n";
        cycles = 4;
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
        std::cout << "Operation CPL (0x3F) not implemented\n";
        //cycles = cpu.alu8bit->cp_a_hl()
        cycles = 4;
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
        std::cout << "Instruction HALT (0x76) not implemented\n";
        cycles = 4;
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
        cycles = cpu.loads8bit->pop_r16(*cpu.AF);
        break;
    case 0xF2:
        cycles = cpu.loads8bit->ld_a_c();
        break;
    case 0xF3:
        // throw std::runtime_error("Operation DI (0xF3) not implemented");
        std::cout << "Operation DI (0xF3) not implemented\n";
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
        // throw std::runtime_error("Operation EI (0xFB) not implemented");
        std::cout << "Operation EI (0xFB) not implemented\n";
        break;
    case 0xFE:
        cycles = cpu.alu8bit->cp_a_n8();
        break;
    case 0xFF:
        cycles = cpu.jumps->rst(0x38);

    default:
        std::cout << "Illegal opcode " << std::hex << opcode << "\n";
        // throw std::runtime_error("");
        break;
    }

    return 0;
}
