#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/ARM/arm_instructions_MOV.h"

void testMOV();
void testMVN(); 
void testMRS();

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "test") {
            testMOV();
            testMVN();
            testMRS();
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
    cpu.setSPSR(Field::SPSR, 0x12345678); // Set some value in SPSR
    cpu.setCPSR(Field::SPSR, 0x87654321); // Set some value in CPSR
    uint32_t instruction = 0xE10F0000; // Example MRS instruction: MRS R0, CPSR
    executeMRS(cpu, instruction);

    // Check if the register R0 is set to the CPSR value
    if (cpu.getRegister(0) == 0x87654321) {
        std::cout << "MRS instruction test passed." << std::endl;
    } else {
        std::cout << "MRS instruction test failed." << std::endl;
    }
}