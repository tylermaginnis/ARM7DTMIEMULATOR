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

void executeMUL(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rm, and Rs from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute MUL
    uint32_t result = cpu.getRegister(Rm) * cpu.getRegister(Rs);
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeMLA(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rm, Rs, and Rn from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;
    uint32_t Rn = (instruction >> 12) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;
    std::cout << "Rn: " << Rn << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Fetch register values
    uint32_t Rm_val = cpu.getRegister(Rm);
    uint32_t Rs_val = cpu.getRegister(Rs);
    uint32_t Rn_val = cpu.getRegister(Rn);

    // Debug prints for register values
    std::cout << "Rm value: " << std::dec << Rm_val << std::endl;
    std::cout << "Rs value: " << std::dec << Rs_val << std::endl;
    std::cout << "Rn value: " << std::dec << Rn_val << std::endl;

    // Execute MLA
    uint32_t intermediate_result = Rm_val * Rs_val;
    uint32_t result = intermediate_result + Rn_val;
    std::cout << "Intermediate result (Rm_val * Rs_val): " << std::dec << intermediate_result << std::endl;
    std::cout << "Final result (intermediate_result + Rn_val): " << std::dec << result << std::endl;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << std::dec << result << std::endl;
}