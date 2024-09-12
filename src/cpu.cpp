#include "cpu.h"
#include "../include/instructions/ARM/ARMinstruction.h"
#include "../include/instructions/ARM/MOV/MOVinstruction.h"
#include <iostream>
#include <string>

void CPU::executeInstruction(uint32_t instruction) {
    uint32_t opcode = (instruction >> 21) & 0xF;

    ARMInstruction* instr = nullptr;
    switch (opcode) {
        case 0xD: instr = new MOVInstruction(); 
    }

    if (instr) {
        instr->execute(*this, instruction);
        delete instr;
    }
}

void CPU::setRegister(uint32_t reg, uint32_t value) {
    std::cout << "setRegister called with reg: " << reg << ", value: " << std::hex << value << std::endl;
    if (reg < 16) {
        if (reg == 13) { // SP
            std::cout << "Setting SP for mode: " << static_cast<int>(currentMode) << std::endl;
            switch (currentMode) {
                case Mode::FIQ: banked_r13_fiq = value; break;
                case Mode::IRQ: banked_r13_irq = value; break;
                case Mode::SUPERVISOR: banked_r13_svc = value; break;
                case Mode::ABORT: banked_r13_abt = value; break;
                case Mode::UNDEFINED: banked_r13_und = value; break;
                default: registers[13] = value; break;
            }
        } else if (reg == 14) { // LR
            std::cout << "Setting LR for mode: " << static_cast<int>(currentMode) << std::endl;
            switch (currentMode) {
                case Mode::FIQ: banked_r14_fiq = value; break;
                case Mode::IRQ: banked_r14_irq = value; break;
                case Mode::SUPERVISOR: banked_r14_svc = value; break;
                case Mode::ABORT: banked_r14_abt = value; break;
                case Mode::UNDEFINED: banked_r14_und = value; break;
                default: registers[14] = value; break;
            }
        } else if (reg == 15) { // PC
            std::cout << "Setting PC with masking bits [1:0]" << std::endl;
            registers[15] = value & 0xFFFFFFFC; // Mask bits [1:0]
        } else {
            std::cout << "Setting general register: " << reg << std::endl;
            registers[reg] = value;
        }
    }
    std::cout << "Register " << reg << " set to " << std::hex << value << std::endl;
}

uint32_t CPU::getRegister(uint32_t reg) const {
    std::cout << "getRegister called with reg: " << reg << std::endl;
    if (reg < 16) {
        if (reg == 13) { // SP
            std::cout << "Getting SP for mode: " << static_cast<int>(currentMode) << std::endl;
            switch (currentMode) {
                case Mode::FIQ: return banked_r13_fiq;
                case Mode::IRQ: return banked_r13_irq;
                case Mode::SUPERVISOR: return banked_r13_svc;
                case Mode::ABORT: return banked_r13_abt;
                case Mode::UNDEFINED: return banked_r13_und;
                default: return registers[13];
            }
        } else if (reg == 14) { // LR
            std::cout << "Getting LR for mode: " << static_cast<int>(currentMode) << std::endl;
            switch (currentMode) {
                case Mode::FIQ: return banked_r14_fiq;
                case Mode::IRQ: return banked_r14_irq;
                case Mode::SUPERVISOR: return banked_r14_svc;
                case Mode::ABORT: return banked_r14_abt;
                case Mode::UNDEFINED: return banked_r14_und;
                default: return registers[14];
            }
        } else if (reg == 15) { // PC
            std::cout << "Getting PC with masking bits [1:0]" << std::endl;
            return registers[15] & 0xFFFFFFFC; // Mask bits [1:0]
        } else {
            std::cout << "Getting general register: " << reg << std::endl;
            return registers[reg];
        }
    }
    std::cout << "Register " << reg << " value: " << std::hex << 0 << std::endl;
    return 0;
}

bool CPU::checkCondition(Condition cond) {
    std::cout << "checkCondition called with cond: " << static_cast<int>(cond) << std::endl;
    uint32_t flags = cpsr & 0xF0000000; // Extract the flags (NZCV)
    bool N = flags & 0x80000000;
    bool Z = flags & 0x40000000;
    bool C = flags & 0x20000000;
    bool V = flags & 0x10000000;

    std::cout << "Flags - N: " << N << ", Z: " << Z << ", C: " << C << ", V: " << V << std::endl;

    bool result;
    switch (cond) {
        case Condition::EQ: result = Z; break;           // Equal
        case Condition::NE: result = !Z; break;          // Not equal
        case Condition::CS: result = C; break;           // Carry set/unsigned higher or same
        case Condition::CC: result = !C; break;          // Carry clear/unsigned lower
        case Condition::MI: result = N; break;           // Minus/negative
        case Condition::PL: result = !N; break;          // Plus/positive or zero
        case Condition::VS: result = V; break;           // Overflow
        case Condition::VC: result = !V; break;          // No overflow
        case Condition::HI: result = C && !Z; break;     // Unsigned higher
        case Condition::LS: result = !C || Z; break;     // Unsigned lower or same
        case Condition::GE: result = N == V; break;      // Signed greater than or equal
        case Condition::LT: result = N != V; break;      // Signed less than
        case Condition::GT: result = !Z && (N == V); break; // Signed greater than
        case Condition::LE: result = Z || (N != V); break;  // Signed less than or equal
        case Condition::AL: result = true; break;        // Always
        default: result = false; break;                  // Undefined condition
    }
    std::cout << "Condition check result: " << result << std::endl;
    return result;
}

void CPU::updateFlags(uint32_t result) {
    std::cout << "updateFlags called with result: " << std::hex << result << std::endl;
    
    // Update Z flag
    if (result == 0) {
        cpsr |= 0x40000000; // Set Z flag
        std::cout << "Z flag set" << std::endl;
    } else {
        cpsr &= ~0x40000000; // Clear Z flag
        std::cout << "Z flag cleared" << std::endl;
    }

    // Update N flag
    if (result & 0x80000000) {
        cpsr |= 0x80000000; // Set N flag
        std::cout << "N flag set" << std::endl;
    } else {
        cpsr &= ~0x80000000; // Clear N flag
        std::cout << "N flag cleared" << std::endl;
    }

    // Update C and V flags based on specific operations
    // Example for MOV and MVN (you may need to adjust based on your logic)
    // Assuming C and V flags are not affected by MOV and MVN
    // You can add logic here if needed for other instructions
}

void CPU::setCPSR(uint32_t value, uint32_t fieldMask) {
    std::cout << "setCPSR called with value: " << std::hex << value << ", fieldMask: " << fieldMask << std::endl;
    std::cout << "Current CPSR before update: " << std::hex << cpsr << std::endl;

    if (fieldMask == 0xFFFFFFFF) {
        cpsr = value; // Update all bits if fieldMask is all ones
    } else {
        if (fieldMask & 0x1) { // Control field
            cpsr = (cpsr & ~0xFF) | (value & 0xFF);
        }
        if (fieldMask & 0x2) { // Extension field
            cpsr = (cpsr & ~0xFF00) | (value & 0xFF00);
        }
        if (fieldMask & 0x4) { // Status field
            cpsr = (cpsr & ~0xFF0000) | (value & 0xFF0000);
        }
        if (fieldMask & 0x8) { // Flags field
            cpsr = (cpsr & ~0xF0000000) | (value & 0xF0000000);
        }
    }
    std::cout << "Set CPSR: " << std::hex << cpsr << std::endl;
}

void CPU::setSPSR(uint32_t value, uint32_t fieldMask) {
    std::cout << "setSPSR called with value: " << std::hex << value << ", fieldMask: " << fieldMask << std::endl;
    std::cout << "Current SPSR before update: " << std::hex << spsr << std::endl;

    if (fieldMask == 0xFFFFFFFF) {
        spsr = value; // Update all bits if fieldMask is all ones
    } else {
        if (fieldMask & 0x1) { // Control field
            spsr = (spsr & ~0xFF) | (value & 0xFF);
        }
        if (fieldMask & 0x2) { // Extension field
            spsr = (spsr & ~0xFF00) | (value & 0xFF00);
        }
        if (fieldMask & 0x4) { // Status field
            spsr = (spsr & ~0xFF0000) | (value & 0xFF0000);
        }
        if (fieldMask & 0x8) { // Flags field
            spsr = (spsr & ~0xF0000000) | (value & 0xF0000000);
        }
    }
    std::cout << "Set SPSR: " << std::hex << spsr << std::endl;
}

void CPU::handleImmediateValue(uint32_t& registerValue, uint32_t immediateValue, uint32_t fieldMask, bool isCPSR) {
    std::cout << "handleImmediateValue called with immediateValue: " << std::hex << immediateValue << ", fieldMask: " << fieldMask << ", isCPSR: " << isCPSR << std::endl;

    std::cout << "Immediate value: " << std::hex << immediateValue << std::endl;
    uint32_t rotatedValue = immediateValue;
    std::cout << "Rotated value: " << std::hex << rotatedValue << std::endl;

    if (fieldMask == 0xFFFFFFFF) {
        registerValue = rotatedValue;
    } else {
        if (fieldMask & 0x1) { // Control field
            registerValue = (registerValue & ~0xFF) | (rotatedValue & 0xFF);
        }
        if (fieldMask & 0x2) { // Extension field
            registerValue = (registerValue & ~0xFF00) | (rotatedValue & 0xFF00);
        }
        if (fieldMask & 0x4) { // Status field
            registerValue = (registerValue & ~0xFF0000) | (rotatedValue & 0xFF0000);
        }
        if (fieldMask & 0x8) { // Flags field
            registerValue = (registerValue & ~0xF0000000) | ((rotatedValue << 28) & 0xF0000000);
        }
    }
}


uint32_t CPU::getSPSR() {
    std::cout << "getSPSR called" << std::endl;
    std::cout << "Get SPSR: " << std::hex << spsr << std::endl;
    return spsr; // Return the stored SPSR value
}

uint32_t CPU::getCPSR() {
    std::cout << "getCPSR called" << std::endl;
    std::cout << "Get CPSR: " << std::hex << cpsr << std::endl;
    return cpsr; // Return the stored CPSR value
}

void CPU::setCPSRControl(uint32_t value) {
    std::cout << "setCPSRControl called with value: " << std::hex << value << std::endl;
    cpsr = (cpsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
    std::cout << "Set CPSR Control: " << std::hex << cpsr << std::endl;
}

void CPU::setCPSRFlags(uint32_t value) {
    std::cout << "setCPSRFlags called with value: " << std::hex << value << std::endl;
    cpsr = (cpsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
    std::cout << "Set CPSR Flags: " << std::hex << cpsr << std::endl;
}

void CPU::setSPSRControl(uint32_t value) {
    std::cout << "setSPSRControl called with value: " << std::hex << value << std::endl;
    spsr = (spsr & 0xFFFFFF00) | (value & 0xFF); // Update only the control bits
    std::cout << "Set SPSR Control: " << std::hex << spsr << std::endl;
}

void CPU::setSPSRFlags(uint32_t value) {
    std::cout << "setSPSRFlags called with value: " << std::hex << value << std::endl;
    spsr = (spsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update only the flag bits
    std::cout << "Set SPSR Flags: " << std::hex << spsr << std::endl;
}

void CPU::switchMode(Mode mode) {
    std::cout << "switchMode called with mode: " << static_cast<int>(mode) << std::endl;

    // Save current mode's banked registers
    switch (currentMode) {
        case Mode::FIQ:
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
    std::cout << "Switched to mode: " << static_cast<int>(currentMode) << std::endl;

    // Restore new mode's banked registers
    switch (currentMode) {
        case Mode::FIQ:
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
        case Mode::USER:
            // USER mode uses the main registers, no action needed
            break;
        default:
            break;
    }
}

uint32_t CPU::getFlags() const {
    return cpsr & 0xF0000000; // Return only the flag bits (N, Z, C, V)
}

void CPU::resetCPU() {
    // Reset all general-purpose registers to 0
    for (int i = 0; i < 16; ++i) {
        registers[i] = 0;
    }

    // Reset CPSR and SPSR to 0
    cpsr = 0;
    spsr = 0;

    // Reset all banked registers to 0
    banked_r8_fiq = 0;
    banked_r9_fiq = 0;
    banked_r10_fiq = 0;
    banked_r11_fiq = 0;
    banked_r12_fiq = 0;
    banked_r13_fiq = 0;
    banked_r14_fiq = 0;

    banked_r13_irq = 0;
    banked_r14_irq = 0;

    banked_r13_svc = 0;
    banked_r14_svc = 0;

    banked_r13_abt = 0;
    banked_r14_abt = 0;

    banked_r13_und = 0;
    banked_r14_und = 0;

    // Reset the current mode to USER mode
    currentMode = Mode::USER;
}
