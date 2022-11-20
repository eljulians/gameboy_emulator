#include <stdexcept>
#include <iostream>
#include <string>
#include "control_unit.hpp"
#include "cpu.hpp"


uint16_t ControlUnit::fetch() {
    uint16_t opcode = cpu.fetchByte();

    if (opcode == _2_BYTE_OPCODE_PREFIX) {
        opcode = (_2_BYTE_OPCODE_PREFIX << 8) | cpu.fetchByte();
    }

    return opcode;
}


uint8_t ControlUnit::execute() {
    uint16_t opcode = fetch();
    uint8_t cycles;

    std::cout << "Fetched opcode " << std::hex << opcode << "\n";

    switch(opcode) {
        case 0x00:
            break;
        case 0x40:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.B);
            break;
        case 0x41:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.C);
            break;
        case 0x42:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.D);
            break;
        case 0x43:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.E);
            break;
        case 0x44:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.H);
            break;
        case 0x45:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.L);
            break;
        case 0x46:
            cpu.loads8bit->load_r8_hl(cpu.B);
            break;
        case 0x47:
            cpu.loads8bit->load_r8_r8(cpu.B, cpu.A);
            break;
        case 0x48:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.B);
            break;
        case 0x49:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.C);
            break;
        case 0x4A:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.D);
            break;
        case 0x4B:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.E);
            break;
        case 0x4C:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.H);
            break;
        case 0x4D:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.L);
            break;
        case 0x4E:
            cpu.loads8bit->load_r8_hl(cpu.C);
            break;
        case 0x4F:
            cpu.loads8bit->load_r8_r8(cpu.C, cpu.A);
            break;

        case 0x50:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.B);
            break;
        case 0x51:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.C);
            break;
        case 0x52:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.D);
            break;
        case 0x53:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.E);
            break;
        case 0x54:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.H);
            break;
        case 0x55:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.L);
            break;
        case 0x56:
            cpu.loads8bit->load_r8_hl(cpu.D);
            break;
        case 0x57:
            cpu.loads8bit->load_r8_r8(cpu.D, cpu.A);
            break;
        case 0x58:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.B);
            break;
        case 0x59:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.C);
            break;
        case 0x5A:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.D);
            break;
        case 0x5B:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.E);
            break;
        case 0x5C:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.H);
            break;
        case 0x5D:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.L);
            break;
        case 0x5E:
            cpu.loads8bit->load_r8_hl(cpu.E);
            break;
        case 0x5F:
            cpu.loads8bit->load_r8_r8(cpu.E, cpu.A);
            break;

        case 0x60:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.B);
            break;
        case 0x61:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.C);
            break;
        case 0x62:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.D);
            break;
        case 0x63:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.E);
            break;
        case 0x64:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.H);
            break;
        case 0x65:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.L);
            break;
        case 0x66:
            cpu.loads8bit->load_r8_hl(cpu.H);
            break;
        case 0x67:
            cpu.loads8bit->load_r8_r8(cpu.H, cpu.A);
            break;
        case 0x68:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.B);
            break;
        case 0x69:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.C);
            break;
        case 0x6A:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.D);
            break;
        case 0x6B:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.E);
            break;
        case 0x6C:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.H);
            break;
        case 0x6D:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.L);
            break;
        case 0x6E:
            cpu.loads8bit->load_r8_hl(cpu.L);
            break;
        case 0x6F:
            cpu.loads8bit->load_r8_r8(cpu.L, cpu.A);
            break;

        case 0x80:
            cpu.alu8bit->add_a_r8(cpu.B);
            break;
        case 0x81:
            cpu.alu8bit->add_a_r8(cpu.C);
            break;
        case 0x82:
            cpu.alu8bit->add_a_r8(cpu.D);
            break;
        case 0x83:
            cpu.alu8bit->add_a_r8(cpu.E);
            break;
        case 0x84:
            cpu.alu8bit->add_a_r8(cpu.H);
            break;
        case 0x85:
            cpu.alu8bit->add_a_r8(cpu.L);
            break;
        case 0x86:
            cpu.alu8bit->add_a_hl();
            break;
        case 0x87:
            cpu.alu8bit->add_a_r8(cpu.A);
            break;
        case 0x88:
            cpu.alu8bit->adc_a_r8(cpu.B);
            break;
        case 0x89:
            cpu.alu8bit->adc_a_r8(cpu.C);
            break;
        case 0x8A:
            cpu.alu8bit->adc_a_r8(cpu.D);
            break;
        case 0x8B:
            cpu.alu8bit->adc_a_r8(cpu.E);
            break;
        case 0x8C:
            cpu.alu8bit->adc_a_r8(cpu.H);
            break;
        case 0x8D:
            cpu.alu8bit->adc_a_r8(cpu.L);
            break;
        case 0x8E:
            cpu.alu8bit->adc_a_hl();
            break;
        case 0x8F:
            cpu.alu8bit->adc_a_r8(cpu.A);
            break;

        case 0x90:
            cpu.alu8bit->sub_a_r8(cpu.B);
            break;
        case 0x91:
            cpu.alu8bit->sub_a_r8(cpu.C);
            break;
        case 0x92:
            cpu.alu8bit->sub_a_r8(cpu.D);
            break;
        case 0x93:
            cpu.alu8bit->sub_a_r8(cpu.E);
            break;
        case 0x94:
            cpu.alu8bit->sub_a_r8(cpu.H);
            break;
        case 0x95:
            cpu.alu8bit->sub_a_r8(cpu.L);
            break;
        case 0x96:
            cpu.alu8bit->sub_a_hl();
            break;
        case 0x97:
            cpu.alu8bit->sub_a_r8(cpu.A);
            break;
        case 0x98:
            cpu.alu8bit->sbc_a_r8(cpu.B);
            break;
        case 0x99:
            cpu.alu8bit->sbc_a_r8(cpu.C);
            break;
        case 0x9A:
            cpu.alu8bit->sbc_a_r8(cpu.D);
            break;
        case 0x9B:
            cpu.alu8bit->sbc_a_r8(cpu.E);
            break;
        case 0x9C:
            cpu.alu8bit->sbc_a_r8(cpu.H);
            break;
        case 0x9D:
            cpu.alu8bit->sbc_a_r8(cpu.L);
            break;
        case 0x9E:
            cpu.alu8bit->sbc_a_hl();
            break;
        case 0x9F:
            cpu.alu8bit->sbc_a_r8(cpu.A);
            break;

        case 0xA0:
            cpu.alu8bit->and_a_r8(cpu.B);
            break;
        case 0xA1:
            cpu.alu8bit->and_a_r8(cpu.C);
            break;
        case 0xA2:
            cpu.alu8bit->and_a_r8(cpu.D);
            break;
        case 0xA3:
            cpu.alu8bit->and_a_r8(cpu.E);
            break;
        case 0xA4:
            cpu.alu8bit->and_a_r8(cpu.H);
            break;
        case 0xA5:
            cpu.alu8bit->and_a_r8(cpu.L);
            break;
        case 0xA6:
            cpu.alu8bit->and_a_hl();
            break;
        case 0xA7:
            cpu.alu8bit->and_a_r8(cpu.A);
            break;
        case 0xA8:
            cpu.alu8bit->xor_a_r8(cpu.B);
            break;
        case 0xA9:
            cpu.alu8bit->xor_a_r8(cpu.C);
            break;
        case 0xAA:
            cpu.alu8bit->xor_a_r8(cpu.D);
            break;
        case 0xAB:
            cpu.alu8bit->xor_a_r8(cpu.E);
            break;
        case 0xAC:
            cpu.alu8bit->xor_a_r8(cpu.H);
            break;
        case 0xAD:
            cpu.alu8bit->xor_a_r8(cpu.L);
            break;
        case 0xAE:
            cpu.alu8bit->xor_a_hl();
            break;
        case 0xAF:
            cpu.alu8bit->xor_a_r8(cpu.A);
            break;

        case 0xB0:
            cpu.alu8bit->or_a_r8(cpu.B);
            break;
        case 0xB1:
            cpu.alu8bit->or_a_r8(cpu.C);
            break;
        case 0xB2:
            cpu.alu8bit->or_a_r8(cpu.D);
            break;
        case 0xB3:
            cpu.alu8bit->or_a_r8(cpu.E);
            break;
        case 0xB4:
            cpu.alu8bit->or_a_r8(cpu.H);
            break;
        case 0xB5:
            cpu.alu8bit->or_a_r8(cpu.L);
            break;
        case 0xB6:
            cpu.alu8bit->or_a_hl();
            break;
        case 0xB7:
            cpu.alu8bit->or_a_r8(cpu.A);
            break;
        case 0xB8:
            cpu.alu8bit->cp_a_r8(cpu.B);
            break;
        case 0xB9:
            cpu.alu8bit->cp_a_r8(cpu.C);
            break;
        case 0xBA:
            cpu.alu8bit->cp_a_r8(cpu.D);
            break;
        case 0xBB:
            cpu.alu8bit->cp_a_r8(cpu.E);
            break;
        case 0xBC:
            cpu.alu8bit->cp_a_r8(cpu.H);
            break;
        case 0xBD:
            cpu.alu8bit->cp_a_r8(cpu.L);
            break;
        case 0xBE:
            cpu.alu8bit->cp_a_hl();
            break;
        case 0xBF:
            cpu.alu8bit->cp_a_r8(cpu.A);
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
            //throw std::runtime_error("Operation DI (0xF3) not implemented");
            std::cout << "Operation DI (0xF3) not implemented";
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
            //throw std::runtime_error("Operation EI (0xFB) not implemented");
            std::cout << "Operation EI (0xFB) not implemented";
            break;
        case 0xFE:
            cycles = cpu.alu8bit->cp_a_n8();
            break;
        case 0xFF:
            cycles = cpu.jumps->rst(0x38);

        default:
            std::cout << "Illegal opcode " << std::hex << opcode << "\n";
            //throw std::runtime_error("");
            break;
    }    

    return 0;
}