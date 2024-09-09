#include "../../include/ARM/arm_instructions_MOV.h"

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

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        return;
    }

    // Execute MVN (bitwise NOT of Oprnd2)
    uint32_t result = ~Oprnd2;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
    }
}

void executeMRS(CPU& cpu, uint32_t instruction) {
    // Extract condition, Rd, and PSR field from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t psr = (instruction >> 22) & 0x1; // 0 for CPSR, 1 for SPSR

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        return;
    }

    // Execute MRS
    uint32_t value = (psr == 0) ? cpu.getCPSR() : cpu.getSPSR();
    cpu.setRegister(Rd, value);
}