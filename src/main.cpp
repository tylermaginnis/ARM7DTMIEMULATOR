#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/ARM/arm_instructions_MOV.h"
#include "../include/ARM/arm_instructions_ARITHMETIC.h"

// MOV tests
void testMOV(CPU& cpu);
void testMVN(CPU& cpu); 
void testMRS(CPU& cpu);
void testMSR(CPU& cpu);
void testMSRImmediate(CPU& cpu);

// ARITHMETIC tests
void testADD(CPU& cpu);
void testADC(CPU& cpu);
void testSUB(CPU& cpu);
void testSBC(CPU& cpu);
void testRSB(CPU& cpu);
void testRSC(CPU& cpu);
void testMUL(CPU& cpu);
void testMLA(CPU& cpu);
void testUMULL(CPU& cpu);
void testUMLAL(CPU& cpu);
void testSMULL(CPU& cpu);
void testSMLAL(CPU& cpu);
void testCMP(CPU& cpu);
void testCMN(CPU& cpu);

void testSwitchMode(CPU& cpu);

int main(int argc, char* argv[]) {
    CPU cpu; // Create a single CPU instance

    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "test") {
            // MOV tests
            testMOV(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMVN(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMRS(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMSR(cpu); 
            std::cout << "-----------------------------------------" << std::endl;
            testMSRImmediate(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            // ARITHMETIC TESTS
            testADD(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testADC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSUB(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSBC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testRSB(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testRSC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMUL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMLA(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testUMULL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testUMLAL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSMULL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSMLAL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testCMP(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testCMN(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            //testSwitchMode(cpu);
            //std::cout << "-----------------------------------------" << std::endl;
            return 0;
        }
    }

    // Add any initialization or main code here

    return 0;
}

void testMOV(CPU& cpu) {
    uint32_t instruction = 0xE3A01001; // Example MOV instruction: MOV R1, #1
    executeMOV(cpu, instruction);

    // Check if the register R1 is set to 1
    if (cpu.getRegister(1) == 1) {
        std::cout << "MOV instruction test passed." << std::endl;
    } else {
        std::cout << "MOV instruction test failed." << std::endl;
    }
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


void testSwitchMode(CPU& cpu) {
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

void testADD(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    uint32_t instruction = 0xE2811003; // Example ADD instruction: ADD R1, R1, #3
    executeADD(cpu, instruction);

    // Check if the register R1 is set to 8
    if (cpu.getRegister(1) == 8) {
        std::cout << "ADD instruction test passed." << std::endl;
    } else {
        std::cout << "ADD instruction test failed." << std::endl;
    }
}

void testADC(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    cpu.setRegister(2, 3); // Set R2 to 3
    cpu.setCPSR(0x20000000, 0xFFFFFFFF); // Set carry flag in CPSR

    uint32_t instruction = 0xE0A11002; // Correct ADC instruction: ADC R1, R1, R2
    executeADC(cpu, instruction);

    // Check if the register R1 is set to 9 (5 + 3 + 1)
    if (cpu.getRegister(1) == 9) {
        std::cout << "ADC instruction test passed." << std::endl;
    } else {
        std::cout << "ADC instruction test failed." << std::endl;
    }
}

void testSUB(CPU& cpu) {
    cpu.setRegister(1, 10); // Set R1 to 10
    uint32_t instruction = 0xE2411003; // Example SUB instruction: SUB R1, R1, #3
    executeSUB(cpu, instruction);

    // Check if the register R1 is set to 7
    if (cpu.getRegister(1) == 7) {
        std::cout << "SUB instruction test passed." << std::endl;
    } else {
        std::cout << "SUB instruction test failed." << std::endl;
    }
}

void testSBC(CPU& cpu) {
    cpu.setRegister(1, 10); // Set R1 to 10
    cpu.setRegister(2, 3); // Set R2 to 3
    cpu.setCPSR(0x20000000, 0xFFFFFFFF); // Set carry flag in CPSR

    uint32_t instruction = 0xE0C11002; // Correct SBC instruction: SBC R1, R1, R2
    executeSBC(cpu, instruction);

    // Check if the register R1 is set to 7 (10 - 3 - (1 - 1))
    if (cpu.getRegister(1) == 7) {
        std::cout << "SBC instruction test passed." << std::endl;
    } else {
        std::cout << "SBC instruction test failed." << std::endl;
    }
}

void testRSB(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    uint32_t instruction = 0xE2611003; // Example RSB instruction: RSB R1, R1, #3
    executeRSB(cpu, instruction);

    // Check if the register R1 is set to -2 (3 - 5)
    if (cpu.getRegister(1) == static_cast<uint32_t>(-2)) {
        std::cout << "RSB instruction test passed." << std::endl;
    } else {
        std::cout << "RSB instruction test failed." << std::endl;
    }
}

void testRSC(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    cpu.setCPSR(0x20000000, 0xFFFFFFFF); // Set carry flag in CPSR
    uint32_t instruction = 0xE0E11002; // Example RSC instruction: RSC R1, R1, R2
    executeRSC(cpu, instruction);

    // Check if the register R1 is set to -3 (2 - 5 - (1 - 1))
    if (cpu.getRegister(1) == static_cast<uint32_t>(-3)) {
        std::cout << "RSC instruction test passed." << std::endl;
    } else {
        std::cout << "RSC instruction test failed." << std::endl;
    }
}

void testMUL(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    cpu.setRegister(2, 3); // Set R2 to 3
    uint32_t instruction = 0xE0010291; // Example MUL instruction: MUL R1, R2, R1
    executeMUL(cpu, instruction);

    // Check if the register R1 is set to 15 (5 * 3)
    if (cpu.getRegister(1) == 15) {
        std::cout << "MUL instruction test passed." << std::endl;
    } else {
        std::cout << "MUL instruction test failed." << std::endl;
    }
}

void testMLA(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    cpu.setRegister(2, 3); // Set R2 to 3
    cpu.setRegister(3, 10); // Set R3 to 10
    uint32_t instruction = 0xE0211392; // Example MLA instruction: MLA R1, R2, R3, R1
    executeMLA(cpu, instruction);

    // Check if the register R1 is set to 25 (5 * 3 + 10)
    std::cout << "R1: " << (cpu.getRegister(1) == 35) << std::endl;
    if (cpu.getRegister(1) == 35) {
        std::cout << "MLA instruction test passed." << std::endl;
    } else {
        std::cout << "MLA instruction test failed." << std::endl;
    }
}

void testUMULL(CPU& cpu) {
    cpu.setRegister(3, 0xA); // Set R3 to 10
    cpu.setRegister(4, 0xCCCCCCCC); // Set R4 to a large value

    uint32_t instruction = 0xE0830493; // Example UMULL instruction: UMULL R0, R3, R3, R4
    executeUMULL(cpu, instruction);

    // Check if the registers R0 and R3 are set correctly
    uint64_t expected_result = static_cast<uint64_t>(0xA) * static_cast<uint64_t>(0xCCCCCCCC);
    uint32_t expected_resultLo = static_cast<uint32_t>(expected_result & 0xFFFFFFFF);
    uint32_t expected_resultHi = static_cast<uint32_t>((expected_result >> 32) & 0xFFFFFFFF);

    if (cpu.getRegister(0) == expected_resultLo && cpu.getRegister(3) == expected_resultHi) {
        std::cout << "UMULL instruction test passed." << std::endl;
    } else {
        std::cout << "UMULL instruction test failed." << std::endl;
    }
}

void testUMLAL(CPU& cpu) {
    cpu.setRegister(1, 0xFFFFFFFF); // Set R1 to 0xFFFFFFFF
    cpu.setRegister(2, 0xFFFFFFFE); // Set R2 to 0xFFFFFFFE
    cpu.setRegister(3, 0x12345678); // Set R3 to 0x12345678
    cpu.setRegister(4, 0x9ABCDEF0); // Set R4 to 0x9ABCDEF0

    uint32_t instruction = 0xE0E12392; // Example UMLAL instruction: UMLAL R2, R1, R2, R3
    executeUMLAL(cpu, instruction);

    // Check if the registers R2 and R1 are set correctly
    uint64_t initial_value = (static_cast<uint64_t>(0xFFFFFFFF) << 32) | 0xFFFFFFFE;
    uint64_t multiplication_result = static_cast<uint64_t>(0xFFFFFFFE) * static_cast<uint64_t>(0x12345678);
    uint64_t expected_result = initial_value + multiplication_result;
    uint32_t expected_resultLo = static_cast<uint32_t>(expected_result & 0xFFFFFFFF);
    uint32_t expected_resultHi = static_cast<uint32_t>((expected_result >> 32) & 0xFFFFFFFF);

    if (cpu.getRegister(2) == expected_resultLo && cpu.getRegister(1) == expected_resultHi) {
        std::cout << "UMLAL instruction test passed." << std::endl;
    } else {
        std::cout << "UMLAL instruction test failed." << std::endl;
    }
}

void testSMULL(CPU& cpu) {
    cpu.setRegister(3, 0xFFFFFFF6); // Set R3 to -10 (in 32-bit two's complement)
    cpu.setRegister(4, 0xCCCCCCCC); // Set R4 to a large value

    uint32_t instruction = 0xE0830493; // Example SMULL instruction: SMULL R0, R3, R3, R4
    executeSMULL(cpu, instruction);

    // Check if the registers R0 and R3 are set correctly
    int64_t expected_result = static_cast<int64_t>(static_cast<int32_t>(0xFFFFFFF6)) * static_cast<int64_t>(0xCCCCCCCC);
    uint32_t expected_resultLo = static_cast<uint32_t>(expected_result & 0xFFFFFFFF);
    uint32_t expected_resultHi = static_cast<uint32_t>((expected_result >> 32) & 0xFFFFFFFF);

    if (cpu.getRegister(0) == expected_resultLo && cpu.getRegister(3) == expected_resultHi) {
        std::cout << "SMULL instruction test passed." << std::endl;
    } else {
        std::cout << "SMULL instruction test failed." << std::endl;
        std::cout << "Expected R0: " << std::hex << expected_resultLo << ", Got: " << cpu.getRegister(0) << std::endl;
        std::cout << "Expected R3: " << std::hex << expected_resultHi << ", Got: " << cpu.getRegister(3) << std::endl;
    }
}

void testSMLAL(CPU& cpu) {
    cpu.setRegister(1, 0xFFFFFFFF); // Set R1 to 0xFFFFFFFF
    cpu.setRegister(2, 0xFFFFFFFE); // Set R2 to 0xFFFFFFFE
    cpu.setRegister(3, 0x12345678); // Set R3 to 0x12345678
    cpu.setRegister(4, 0x9ABCDEF0); // Set R4 to 0x9ABCDEF0

    uint32_t instruction = 0xE0E12392; // Example SMLAL instruction: SMLAL R2, R1, R2, R3
    executeSMLAL(cpu, instruction);

    // Check if the registers R2 and R1 are set correctly
    int64_t initial_value = (static_cast<int64_t>(0xFFFFFFFF) << 32) | 0xFFFFFFFE;
    int64_t multiplication_result = static_cast<int64_t>(static_cast<int32_t>(0xFFFFFFFE)) * static_cast<int64_t>(0x12345678);
    int64_t expected_result = initial_value + multiplication_result;
    uint32_t expected_resultLo = static_cast<uint32_t>(expected_result & 0xFFFFFFFF);
    uint32_t expected_resultHi = static_cast<uint32_t>((expected_result >> 32) & 0xFFFFFFFF);

    if (cpu.getRegister(2) == expected_resultLo && cpu.getRegister(1) == expected_resultHi) {
        std::cout << "SMLAL instruction test passed." << std::endl;
    } else {
        std::cout << "SMLAL instruction test failed." << std::endl;
        std::cout << "Expected R2: " << std::hex << expected_resultLo << ", Got: " << cpu.getRegister(2) << std::endl;
        std::cout << "Expected R1: " << std::hex << expected_resultHi << ", Got: " << cpu.getRegister(1) << std::endl;
    }
}

void testCMP(CPU& cpu) {
    cpu.setRegister(1, 0xA); // Set R1 to 10
    uint32_t instruction = 0xE3510005; // Example CMP instruction: CMP R1, #5
    executeCMP(cpu, instruction);

    // Check if the flags are set correctly (10 - 5)
    uint32_t expected_flags = 0x20000000; // Only the C flag should be set
    if (cpu.getFlags() == expected_flags) {
        std::cout << "CMP instruction test passed." << std::endl;
    } else {
        std::cout << "CMP instruction test failed." << std::endl;
        std::cout << "Expected flags: " << std::hex << expected_flags << ", Got: " << cpu.getFlags() << std::endl;
    }
}

void testCMN(CPU& cpu) {
    cpu.setRegister(1, 0xA); // Set R1 to 10
    uint32_t instruction = 0xE3710005; // Example CMN instruction: CMN R1, #5
    executeCMN(cpu, instruction);

    // Check if the flags are set correctly (10 + 5)
    uint32_t expected_flags = 0x20000000; // Only the C flag should be set
    if ((cpu.getCPSR() & 0xF0000000) == expected_flags) {
        std::cout << "CMN instruction test passed." << std::endl;
    } else {
        std::cout << "CMN instruction test failed." << std::endl;
        std::cout << "Expected flags: " << std::hex << expected_flags << ", Got: " << (cpu.getCPSR() & 0xF0000000) << std::endl;
    }
}