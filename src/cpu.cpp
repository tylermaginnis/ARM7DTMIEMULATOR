#include "cpu.h"
#include <iostream>
#include <string>

void CPU::setRegister(uint32_t reg, uint32_t value) {
    if (reg < 16) {
        if (reg == 13) { // SP
            switch (currentMode) {
                case Mode::FIQ: banked_r13_fiq = value; break;
                case Mode::IRQ: banked_r13_irq = value; break;
                case Mode::SUPERVISOR: banked_r13_svc = value; break;
                case Mode::ABORT: banked_r13_abt = value; break;
                case Mode::UNDEFINED: banked_r13_und = value; break;
                default: registers[13] = value; break;
            }
        } else if (reg == 14) { // LR
            switch (currentMode) {
                case Mode::FIQ: banked_r14_fiq = value; break;
                case Mode::IRQ: banked_r14_irq = value; break;
                case Mode::SUPERVISOR: banked_r14_svc = value; break;
                case Mode::ABORT: banked_r14_abt = value; break;
                case Mode::UNDEFINED: banked_r14_und = value; break;
                default: registers[14] = value; break;
            }
        } else if (reg == 15) { // PC
            registers[15] = value & 0xFFFFFFFC; // Mask bits [1:0]
        } else {
            registers[reg] = value;
        }
    }
}

uint32_t CPU::getRegister(uint32_t reg) {
    if (reg < 16) {
        if (reg == 13) { // SP
            switch (currentMode) {
                case Mode::FIQ: return banked_r13_fiq;
                case Mode::IRQ: return banked_r13_irq;
                case Mode::SUPERVISOR: return banked_r13_svc;
                case Mode::ABORT: return banked_r13_abt;
                case Mode::UNDEFINED: return banked_r13_und;
                default: return registers[13];
            }
        } else if (reg == 14) { // LR
            switch (currentMode) {
                case Mode::FIQ: return banked_r14_fiq;
                case Mode::IRQ: return banked_r14_irq;
                case Mode::SUPERVISOR: return banked_r14_svc;
                case Mode::ABORT: return banked_r14_abt;
                case Mode::UNDEFINED: return banked_r14_und;
                default: return registers[14];
            }
        } else if (reg == 15) { // PC
            return registers[15] & 0xFFFFFFFC; // Mask bits [1:0]
        } else {
            return registers[reg];
        }
    }
    return 0;
}

bool CPU::checkCondition(Condition cond) {
    uint32_t flags = cpsr & 0xF0000000; // Extract the flags (NZCV)
    bool N = flags & 0x80000000;
    bool Z = flags & 0x40000000;
    bool C = flags & 0x20000000;
    bool V = flags & 0x10000000;

    switch (cond) {
        case Condition::EQ: return Z;           // Equal
        case Condition::NE: return !Z;          // Not equal
        case Condition::CS: return C;           // Carry set/unsigned higher or same
        case Condition::CC: return !C;          // Carry clear/unsigned lower
        case Condition::MI: return N;           // Minus/negative
        case Condition::PL: return !N;          // Plus/positive or zero
        case Condition::VS: return V;           // Overflow
        case Condition::VC: return !V;          // No overflow
        case Condition::HI: return C && !Z;     // Unsigned higher
        case Condition::LS: return !C || Z;     // Unsigned lower or same
        case Condition::GE: return N == V;      // Signed greater than or equal
        case Condition::LT: return N != V;      // Signed less than
        case Condition::GT: return !Z && (N == V); // Signed greater than
        case Condition::LE: return Z || (N != V);  // Signed less than or equal
        case Condition::AL: return true;        // Always
        default: return false;                  // Undefined condition
    }
}

void CPU::updateFlags(uint32_t result) {
    if (result == 0) {
        cpsr |= 0x40000000; // Set Z flag
    } else {
        cpsr &= ~0x40000000; // Clear Z flag
    }

    if (result & 0x80000000) {
        cpsr |= 0x80000000; // Set N flag
    } else {
        cpsr &= ~0x80000000; // Clear N flag
    }

    // Note: C and V flags are not updated here. They should be updated based on the specific operation.
}

void CPU::setCPSR(Field field, uint32_t value) {
    std::cout << "Current CPSR before update: " << std::hex << cpsr << std::endl;
    switch (field) {
        case Field::CONTROL:
            cpsr = (cpsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
            break;
        case Field::FLAGS:
            cpsr = (cpsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
            break;
        case Field::CPSR:
            cpsr = value; // Update all bits
            break;
        default:
            break;
    }
    std::cout << "Set CPSR: " << std::hex << cpsr << std::endl;
}

void CPU::setSPSR(Field field, uint32_t value) {
    std::cout << "Current SPSR before update: " << std::hex << spsr << std::endl;
    switch (field) {
        case Field::CONTROL:
            spsr = (spsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
            break;
        case Field::FLAGS:
            spsr = (spsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
            break;
        case Field::SPSR:
            spsr = value; // Update all bits
            break;
        default:
            break;
    }
    std::cout << "Set SPSR: " << std::hex << spsr << std::endl;
}

uint32_t CPU::getSPSR() {
    std::cout << "Get SPSR: " << std::hex << spsr << std::endl;
    return spsr; // Return the stored SPSR value
}

uint32_t CPU::getCPSR() {
    std::cout << "Get CPSR: " << std::hex << cpsr << std::endl;
    return cpsr; // Return the stored CPSR value
}

void CPU::setCPSRControl(uint32_t value) {
    cpsr = (cpsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
}

void CPU::setCPSRFlags(uint32_t value) {
    cpsr = (cpsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
}

void CPU::setSPSRControl(uint32_t value) {
    spsr = (spsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
}

void CPU::setSPSRFlags(uint32_t value) {
    spsr = (spsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
}

void CPU::switchMode(Mode mode) {
    // Save current mode's banked registers
    switch (currentMode) {
        case Mode::FIQ:
            banked_r8_fiq = registers[8];
            banked_r9_fiq = registers[9];
            banked_r10_fiq = registers[10];
            banked_r11_fiq = registers[11];
            banked_r12_fiq = registers[12];
            banked_r13_fiq = registers[13];
            banked_r14_fiq = registers[14];
            break;
        case Mode::IRQ:
            banked_r13_irq = registers[13];
            banked_r14_irq = registers[14];
            break;
        case Mode::SUPERVISOR:
            banked_r13_svc = registers[13];
            banked_r14_svc = registers[14];
            break;
        case Mode::ABORT:
            banked_r13_abt = registers[13];
            banked_r14_abt = registers[14];
            break;
        case Mode::UNDEFINED:
            banked_r13_und = registers[13];
            banked_r14_und = registers[14];
            break;
        default:
            break;
    }

    // Switch mode
    currentMode = mode;

    // Restore new mode's banked registers
    switch (currentMode) {
        case Mode::FIQ:
            registers[8] = banked_r8_fiq;
            registers[9] = banked_r9_fiq;
            registers[10] = banked_r10_fiq;
            registers[11] = banked_r11_fiq;
            registers[12] = banked_r12_fiq;
            registers[13] = banked_r13_fiq;
            registers[14] = banked_r14_fiq;
            break;
        case Mode::IRQ:
            registers[13] = banked_r13_irq;
            registers[14] = banked_r14_irq;
            break;
        case Mode::SUPERVISOR:
            registers[13] = banked_r13_svc;
            registers[14] = banked_r14_svc;
            break;
        case Mode::ABORT:
            registers[13] = banked_r13_abt;
            registers[14] = banked_r14_abt;
            break;
        case Mode::UNDEFINED:
            registers[13] = banked_r13_und;
            registers[14] = banked_r14_und;
            break;
        default:
            break;
    }
}