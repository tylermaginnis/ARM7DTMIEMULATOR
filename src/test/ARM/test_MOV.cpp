#include "../../../include/test/ARM/test_MOV.h"
#include <iostream>



void testMOV(CPU& cpu) {
    // Condition passes, S bit is set, and Rd is R15
    uint32_t instruction = 0xE3B0F001; // Example MOV instruction: MOV R15, #1 (S bit set)
    executeMOV(cpu, instruction);

    // Check if the register R15 is set to 1 and SPSR is copied to CPSR
    if (cpu.getRegister(15) == 1 && cpu.getCPSR() == cpu.getSPSR()) {
        std::cout << "MOV instruction test passed (R15, S bit set)." << std::endl;
    } else {
        std::cout << "MOV instruction test failed (R15, S bit set)." << std::endl;
    }

    cpu.resetCPU();

    // Condition passes, S bit is set, and Rd is not R15
    instruction = 0xE3B01001; // Example MOV instruction: MOV R1, #1 (S bit set)
    executeMOV(cpu, instruction);

    // Check if the register R1 is set to 1 and flags are updated
    if (cpu.getRegister(1) == 1 && (cpu.getFlags() & 0xF0000000) != 0) {
        std::cout << "MOV instruction test passed (R1, S bit set)." << std::endl;
    } else {
        std::cout << "MOV instruction test failed (R1, S bit set)." << std::endl;
    }

    cpu.resetCPU();

    // Condition passes, S bit is not set
    instruction = 0xE1A01001; // Example MOV instruction: MOV R1, R1 (S bit not set)
    executeMOV(cpu, instruction);

    // Check if the register R1 is unchanged and flags are not updated
    if (cpu.getRegister(1) == 1 && (cpu.getFlags() & 0xF0000000) == 0) {
        std::cout << "MOV instruction test passed (S bit not set)." << std::endl;
    } else {
        std::cout << "MOV instruction test failed (S bit not set)." << std::endl;
    }

    cpu.resetCPU();

 
    instruction = 0x03A01001; // Example MOV instruction: MOV R1, #1 (Condition fails)
    executeMOV(cpu, instruction);

    // Check if the register R1 is unchanged
    if (cpu.getRegister(1) == 0) {
        std::cout << "MOV instruction test passed (Condition fails)." << std::endl;
    } else {
        std::cout << "MOV instruction test failed (Condition fails)." << std::endl;
    }

    cpu.resetCPU();
}


void testMVN(CPU& cpu) {
    uint32_t instruction = 0xE3E01001; // Example MVN instruction: MVN R1, #1
    executeMVN(cpu, instruction);

    // Check if the register R1 is set to ~1 (0xFFFFFFFE)
    if (cpu.getRegister(1) == 0xFFFFFFFE) {
        std::cout << "MVN instruction test passed." << std::endl;
    } else {
        std::cout << "MVN instruction test failed." << std::endl;
    }
}

void testMRS(CPU& cpu) {
    cpu.setSPSR(0x12345678, 0xFFFFFFFF); // Set some value in SPSR
    cpu.setCPSR(0x87654321, 0xFFFFFFFF); // Set some value in CPSR
    uint32_t instruction = 0xE10F0000; // Example MRS instruction: MRS R0, CPSR
    executeMRS(cpu, instruction);

    // Check if the register R0 is set to the CPSR value
    if (cpu.getRegister(0) == 0x87654321) {
        std::cout << "MRS CPSR instruction test passed." << std::endl;
    } else {
        std::cout << "MRS CPSR instruction test failed." << std::endl;
    }

    instruction = 0xE14F0000; // Example MRS instruction: MRS R0, SPSR
    executeMRS(cpu, instruction);

    // Check if the register R0 is set to the SPSR value
    if (cpu.getRegister(0) == 0x12345678) {
        std::cout << "MRS SPSR instruction test passed." << std::endl;
    } else {
        std::cout << "MRS SPSR instruction test failed." << std::endl;
    }
}

void testMSR(CPU& cpu) {
    cpu.setRegister(1, 0x87654321); // Set some value in R1
    uint32_t instruction = 0xE129F001; // Example MSR instruction: MSR CPSR, R1
    executeMSR(cpu, instruction);

    // Check if the CPSR is set to the value in R1
    if (cpu.getCPSR() == 0x87654321) {
        std::cout << "MSR CPSR instruction test passed." << std::endl;
    } else {
        std::cout << "MSR CPSR instruction test failed." << std::endl;
    }

    cpu.setRegister(2, 0x12345678); // Set some value in R2
    instruction = 0xE169F002; // Example MSR instruction: MSR SPSR, R2
    executeMSR(cpu, instruction);

    // Check if the SPSR is set to the value in R2
    if (cpu.getSPSR() == 0x12345678) {
        std::cout << "MSR SPSR instruction test passed." << std::endl;
    } else {
        std::cout << "MSR SPSR instruction test failed." << std::endl;
    }
}

void testMSRImmediate(CPU& cpu) {
    uint32_t instruction = 0xE32EF001;  // MSR CPSR_f, #1 (set flags to 1)
    std::cout << "Testing instruction: " << std::hex << instruction << std::endl;
    executeMSRImmediate(cpu, instruction);

    // Debug print
    std::cout << "CPSR: " << std::hex << cpu.getCPSR() << std::endl;

    // Check if the CPSR flags are set correctly
    uint32_t expectedCPSR = (cpu.getCPSR() & ~0xF0000000) | (0x1 << 28);  // Masking and setting expected value
    if ((cpu.getCPSR() & 0xF0000000) == (0x1 << 28)) {
        std::cout << "MSR CPSR immediate instruction test passed." << std::endl;
    } else {
        std::cout << "MSR CPSR immediate instruction test failed." << std::endl;
    }

    instruction = 0xE36EF002;  // MSR SPSR_f, #2 (set flags to 2)
    std::cout << "Testing instruction: " << std::hex << instruction << std::endl;
    executeMSRImmediate(cpu, instruction);

    // Debug print
    std::cout << "SPSR: " << std::hex << cpu.getSPSR() << std::endl;

    // Check if the SPSR flags are set correctly
    uint32_t expectedSPSR = (cpu.getSPSR() & ~0xF0000000) | (0x2 << 28);  // Masking and setting expected value
    if ((cpu.getSPSR() & 0xF0000000) == (0x2 << 28)) {
        std::cout << "MSR SPSR immediate instruction test passed." << std::endl;
    } else {
        std::cout << "MSR SPSR immediate instruction test failed." << std::endl;
    }
}