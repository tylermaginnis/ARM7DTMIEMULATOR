#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/ARM/arm_instructions_MOV.h"

void testMOV();
void testMVN(); 
void testMRS();
void testMSR();
void testMSRImmediate();
void testSwitchMode();

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "test") {
            testMOV();
            std::cout << "-----------------------------------------" << std::endl;
            testMVN();
            std::cout << "-----------------------------------------" << std::endl;
            testMRS();
            std::cout << "-----------------------------------------" << std::endl;
            testMSR(); 
            std::cout << "-----------------------------------------" << std::endl;
            testMSRImmediate();
            std::cout << "-----------------------------------------" << std::endl;
            testSwitchMode();
            std::cout << "-----------------------------------------" << std::endl;
            // Add calls to other test functions here
            return 0;
        }
    }

    CPU cpu;
    // Add any initialization or main code here

    return 0;
}

void testMOV() {
    CPU cpu;
    uint32_t instruction = 0xE3A01001; // Example MOV instruction: MOV R1, #1
    executeMOV(cpu, instruction);

    // Check if the register R1 is set to 1
    if (cpu.getRegister(1) == 1) {
        std::cout << "MOV instruction test passed." << std::endl;
    } else {
        std::cout << "MOV instruction test failed." << std::endl;
    }
}

void testMVN() {
    CPU cpu;
    uint32_t instruction = 0xE3E01001; // Example MVN instruction: MVN R1, #1
    executeMVN(cpu, instruction);

    // Check if the register R1 is set to ~1 (0xFFFFFFFE)
    if (cpu.getRegister(1) == 0xFFFFFFFE) {
        std::cout << "MVN instruction test passed." << std::endl;
    } else {
        std::cout << "MVN instruction test failed." << std::endl;
    }
}

void testMRS() {
    CPU cpu;
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

void testMSR() {
    CPU cpu;
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

void testMSRImmediate() {
    CPU cpu;
    uint32_t instruction = 0xE32EF001;  // MSR CPSR_f, #1 (set flags to 1)
    executeMSRImmediate(cpu, instruction);

    // Debug print
    std::cout << "CPSR: " << std::hex << cpu.getCPSR() << std::endl;

    // Check if the CPSR flags are set to the immediate value in the flags field
    if ((cpu.getCPSR() & 0xF0000000) == 0x10000000) {
        std::cout << "MSR CPSR immediate instruction test passed." << std::endl;
    } else {
        std::cout << "MSR CPSR immediate instruction test failed." << std::endl;
    }

    instruction = 0xE36EF002;  // MSR SPSR_f, #2 (set flags to 2)
    executeMSRImmediate(cpu, instruction);

    // Debug print
    std::cout << "SPSR: " << std::hex << cpu.getSPSR() << std::endl;

    // Check if the SPSR flags are set to the immediate value in the flags field
    if ((cpu.getSPSR() & 0xF0000000) == 0x20000000) {
        std::cout << "MSR SPSR immediate instruction test passed." << std::endl;
    } else {
        std::cout << "MSR SPSR immediate instruction test failed." << std::endl;
    }
}

void testSwitchMode() {
    CPU cpu;
    cpu.switchMode(Mode::USER);
    cpu.setRegister(13, 0x1000); // Set SP in USER mode
    cpu.setRegister(14, 0x2000); // Set LR in USER mode

    cpu.switchMode(Mode::FIQ);
    cpu.setRegister(13, 0x3000); // Set SP in FIQ mode
    cpu.setRegister(14, 0x4000); // Set LR in FIQ mode

    cpu.switchMode(Mode::USER);
    if (cpu.getRegister(13) == 0x1000 && cpu.getRegister(14) == 0x2000) {
        std::cout << "Switch to USER mode test passed." << std::endl;
    } else {
        std::cout << "Switch to USER mode test failed." << std::endl;
    }

    cpu.switchMode(Mode::FIQ);
    if (cpu.getRegister(13) == 0x3000 && cpu.getRegister(14) == 0x4000) {
        std::cout << "Switch to FIQ mode test passed." << std::endl;
    } else {
        std::cout << "Switch to FIQ mode test failed." << std::endl;
    }
}