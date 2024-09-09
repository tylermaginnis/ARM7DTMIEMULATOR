#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/ARM/arm_instructions_MOV.h"

void testMOV();
void testMVN(); // Add this line

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "test") {
            testMOV();
            testMVN(); // Add this line
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