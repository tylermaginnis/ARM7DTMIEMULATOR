#include "../../include/ARM/arm_instructions_MOV.h"
#include <iostream>
#include <string>

void executeMOV(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute MOV
    cpu.setRegister(Rd, Oprnd2);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(Oprnd2);
        std::cout << "Flags updated with " << Oprnd2 << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << Oprnd2 << std::endl;

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(Oprnd2);
        std::cout << "Flags updated with " << Oprnd2 << std::endl;
    }
}

void executeMVN(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute MVN (bitwise NOT of Oprnd2)
    uint32_t result = ~Oprnd2;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
    }

    // Debug print
    std::cout << "Result: " << result << std::endl;

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
    }
}

void executeMRS(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t psr = (instruction >> 22) & 0x1; // 0 for CPSR, 1 for SPSR

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "PSR: " << psr << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t value = (psr == 0) ? cpu.getCPSR() : cpu.getSPSR();
    cpu.setRegister(Rd, value);

    // Debug print
    std::cout << "Register " << Rd << " set to " << std::hex << value << std::endl;
}

void executeMSR(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t fieldMask = (instruction >> 16) & 0xF;
    uint32_t psr = (instruction >> 22) & 0x1; // 0 for CPSR, 1 for SPSR
    uint32_t Rm = (instruction >> 0) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "Field Mask: " << fieldMask << std::endl;
    std::cout << "PSR: " << psr << std::endl;
    std::cout << "Rm: " << Rm << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t value = cpu.getRegister(Rm);
    std::cout << "Value from Rm: " << std::hex << value << std::endl;

    if (psr == 0) { // Update CPSR
        cpu.setCPSR(value, fieldMask);
    } else { // Update SPSR
        cpu.setSPSR(value, fieldMask);
    }

    // Debug prints after update
    std::cout << "Updated CPSR: " << std::hex << cpu.getCPSR() << std::endl;
    std::cout << "Updated SPSR: " << std::hex << cpu.getSPSR() << std::endl;
}

void executeMSRImmediate(CPU& cpu, uint32_t instruction) {
    // Extract condition, field mask, and immediate value from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t fieldMask = (instruction >> 16) & 0xF;  // Field mask for PSR update
    uint32_t psr = (instruction >> 22) & 0x1;        // 0 for CPSR, 1 for SPSR
    uint32_t imm = instruction & 0xFF;               // Immediate value
    uint32_t rotate = (instruction >> 8) & 0xF;      // Rotate right by 2 * rotate

    // Rotate immediate value to the right by 2 * rotate
    uint32_t value = (imm >> (rotate * 2)) | (imm << (32 - (rotate * 2)));
    value &= 0xFFFFFFFF;  // Ensure value is 32-bit

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "Field Mask: " << fieldMask << std::endl;
    std::cout << "PSR: " << psr << std::endl;
    std::cout << "Immediate: " << imm << std::endl;
    std::cout << "Rotate: " << rotate << std::endl;
    std::cout << "Value: " << value << std::endl;

    // Check condition before execution
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;  // Condition failed, do not execute
    }

    // Update the appropriate PSR (CPSR or SPSR) based on the field mask
    if (psr == 0) {  // Update CPSR
        cpu.setCPSR(value, fieldMask);
    } else {  // Update SPSR
        cpu.setSPSR(value, fieldMask);
    }
}