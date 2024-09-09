#include "cpu.h"

void CPU::setRegister(uint32_t reg, uint32_t value) {
    registers[reg] = value;
}

uint32_t CPU::getRegister(uint32_t reg) {
    return registers[reg];
}

bool CPU::checkCondition(Condition cond) {
    // Implement the condition check logic here
    return true; // Placeholder implementation
}

void CPU::updateFlags(uint32_t result) {
    // Implement the flag update logic here
}

void CPU::setCPSR(Field field, uint32_t value) {
    if (field == Field::SPSR) {
        cpsr = value; // Set the CPSR value
    }
}

uint32_t CPU::getCPSR() {
    return cpsr; // Return the stored CPSR value
}

uint32_t CPU::getSPSR() {
    return spsr; // Return the stored SPSR value
}

void CPU::setSPSR(Field field, uint32_t value) {
    if (field == Field::SPSR) {
        spsr = value; // Set the SPSR value
    }
}