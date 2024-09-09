#include "../../include/ARM/arm_instructions_MOV.h"
#include <iostream>
#include <string>

void executeMOV(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        return;
    }

    // Execute MOV
    cpu.setRegister(Rd, Oprnd2);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(Oprnd2);
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

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t value = (psr == 0) ? cpu.getCPSR() : cpu.getSPSR();
    cpu.setRegister(Rd, value);
}

void executeMSR(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t fieldMask = (instruction >> 16) & 0xF;
    uint32_t psr = (instruction >> 22) & 0x1; // 0 for CPSR, 1 for SPSR
    uint32_t Rm = instruction & 0xF;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t value = cpu.getRegister(Rm);

    if (psr == 0) { // Update CPSR
        if (fieldMask & 0x1) { // Control field
            cpu.setCPSR(Field::CONTROL, value & 0xFF);
        }
        if (fieldMask & 0x2) { // Extension field
            cpu.setCPSR(Field::CPSR, (cpu.getCPSR() & 0xFFFF00FF) | (value & 0xFF00));
        }
        if (fieldMask & 0x4) { // Status field
            cpu.setCPSR(Field::CPSR, (cpu.getCPSR() & 0xFF00FFFF) | (value & 0xFF0000));
        }
        if (fieldMask & 0x8) { // Flags field
            cpu.setCPSR(Field::FLAGS, value & 0xF0000000);
        }
    } else { // Update SPSR
        if (fieldMask & 0x1) { // Control field
            cpu.setSPSR(Field::CONTROL, value & 0xFF);
        }
        if (fieldMask & 0x2) { // Extension field
            cpu.setSPSR(Field::SPSR, (cpu.getSPSR() & 0xFFFF00FF) | (value & 0xFF00));
        }
        if (fieldMask & 0x4) { // Status field
            cpu.setSPSR(Field::SPSR, (cpu.getSPSR() & 0xFF00FFFF) | (value & 0xFF0000));
        }
        if (fieldMask & 0x8) { // Flags field
            cpu.setSPSR(Field::FLAGS, value & 0xF0000000);
        }
    }
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
        if (fieldMask & 0x1) {  // Control field (lowest 8 bits)
            cpu.setCPSR(Field::CONTROL, value & 0xFF);  // Only set control bits
        }
        if (fieldMask & 0x2) {  // Extension field (next 8 bits)
            cpu.setCPSR(Field::CPSR, (cpu.getCPSR() & 0xFFFF00FF) | (value & 0xFF00));  // Set extension bits
        }
        if (fieldMask & 0x4) {  // Status field (next 8 bits)
            cpu.setCPSR(Field::CPSR, (cpu.getCPSR() & 0xFF00FFFF) | (value & 0xFF0000));  // Set status bits
        }
        if (fieldMask & 0x8) {  // Flags field (highest 4 bits: NZCV)
            cpu.setCPSR(Field::FLAGS, value & 0xF0000000);  // Set flags in top 4 bits
        }
    } else {  // Update SPSR
        if (fieldMask & 0x1) {  // Control field (lowest 8 bits)
            cpu.setSPSR(Field::CONTROL, value & 0xFF);  // Only set control bits
        }
        if (fieldMask & 0x2) {  // Extension field (next 8 bits)
            cpu.setSPSR(Field::SPSR, (cpu.getSPSR() & 0xFFFF00FF) | (value & 0xFF00));  // Set extension bits
        }
        if (fieldMask & 0x4) {  // Status field (next 8 bits)
            cpu.setSPSR(Field::SPSR, (cpu.getSPSR() & 0xFF00FFFF) | (value & 0xFF0000));  // Set status bits
        }
        if (fieldMask & 0x8) {  // Flags field (highest 4 bits: NZCV)
            cpu.setSPSR(Field::FLAGS, value & 0xF0000000);  // Set flags in top 4 bits
        }
    }
}