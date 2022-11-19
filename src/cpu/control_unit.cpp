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
        default:
            break;
    }    

    return 0;
}