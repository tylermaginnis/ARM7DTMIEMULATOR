#include "../../../../include/instructions/ARM/MOV/MOVinstruction.h"
#include <iostream>

void MOVInstruction::execute(CPU& cpu, uint32_t instruction) {
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

    // If S bit is set and Rd is R15 (PC), copy SPSR to CPSR
    if (S) {
        if (Rd == 15) {
            cpu.setCPSR(cpu.getSPSR(), 0xFFFFFFFF);
        } else {     // Update flags if S bit is set and Rd is not R15 (PC)
            cpu.updateFlags(Oprnd2);
        }
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << Oprnd2 << std::endl;
}