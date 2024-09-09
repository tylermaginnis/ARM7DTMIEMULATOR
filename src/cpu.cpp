#include "cpu.h"
#include <iostream>
#include <string>

void CPU::setRegister(uint32_t reg, uint32_t value) {
    registers[reg] = value;
}

uint32_t CPU::getRegister(uint32_t reg) {
    return registers[reg];
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
            cpsr = (cpsr & 0xFFFFFF00) | (value & 0xFF); // Update control bits
            cpsr = (cpsr & 0xFFFF00FF) | (value & 0xFF00); // Update extension bits
            cpsr = (cpsr & 0xFF00FFFF) | (value & 0xFF0000); // Update status bits
            cpsr = (cpsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update flag bits
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
            spsr = (spsr & 0xFFFFFF00) | (value & 0xFF); // Update control bits
            spsr = (spsr & 0xFFFF00FF) | (value & 0xFF00); // Update extension bits
            spsr = (spsr & 0xFF00FFFF) | (value & 0xFF0000); // Update status bits
            spsr = (spsr & 0x0FFFFFFF) | (value & 0xF0000000); // Update flag bits
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