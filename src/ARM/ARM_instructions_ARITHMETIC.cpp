#include "../../include/ARM/arm_instructions_ARITHMETIC.h"
#include <iostream>
#include <string>

void executeADD(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rn, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute ADD
    uint32_t result = cpu.getRegister(Rn) + Oprnd2;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}


void executeADC(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rn, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF; // Extract Rm as the register operand

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Rm: " << Rm << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Get the carry flag from CPSR
    uint32_t cpsr = cpu.getCPSR();
    std::cout << "Fetching CPSR for carry flag" << std::endl;
    std::cout << "CPSR: " << std::hex << cpsr << std::endl;
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    std::cout << "Carry flag: " << carry << std::endl;

    // Execute ADC
    uint32_t result = cpu.getRegister(Rn) + cpu.getRegister(Rm) + carry;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeSUB(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t result = cpu.getRegister(Rn) - Oprnd2;
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeSBC(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF; // Extract Rm as the register operand

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Rm: " << Rm << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t cpsr = cpu.getCPSR();
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    uint32_t result = cpu.getRegister(Rn) - cpu.getRegister(Rm) - (1 - carry);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeRSB(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t result = Oprnd2 - cpu.getRegister(Rn);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeRSC(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t cpsr = cpu.getCPSR();
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    uint32_t result = Oprnd2 - cpu.getRegister(Rn) - (1 - carry);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}