#include "../../../include/test/ARM/test_ARITHMETIC.h"
#include <iostream>

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

    uint32_t instruction = 0xE0A11092; // Correct ADC instruction with shifter operand: ADC R1, R1, R2, LSL #1
    executeADC(cpu, instruction);

    // Check if the register R1 is set to 12 (5 + (3 << 1) + 1)
    if (cpu.getRegister(1) == 12) {
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
    int64_t multiplication_result = static_cast<int64_t>(0xFFFFFFFE) * static_cast<int64_t>(0x12345678);
    int64_t expected_result = initial_value + multiplication_result;
    uint32_t expected_resultLo = static_cast<uint32_t>(expected_result & 0xFFFFFFFF);
    uint32_t expected_resultHi = static_cast<uint32_t>((expected_result >> 32) &0xFFFFFFFF);
    
    if (cpu.getRegister(2) == expected_resultLo && cpu.getRegister(1) == expected_resultHi) {
        std::cout << "SMLAL instruction test passed." << std::endl;
    } else {
        std::cout << "SMLAL instruction test failed." << std::endl;
    }
}

void testCMP(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    uint32_t instruction = 0xE3510003; // Example CMP instruction: CMP R1, #3
    executeCMP(cpu, instruction);
    // Check if the flags are set correctly (Z flag should be 0, N flag should be 0)
    if ((cpu.getFlags() & 0x40000000) == 0 && (cpu.getFlags() & 0x80000000) == 0) {
        std::cout << "CMP instruction test passed." << std::endl;
    } else {
        std::cout << "CMP instruction test failed." << std::endl;
    }
}

void testCMN(CPU& cpu) {
    cpu.setRegister(1, 5); // Set R1 to 5
    uint32_t instruction = 0xE3710003; // Example CMN instruction: CMN R1, #3
    executeCMN(cpu, instruction);
    // Check if the flags are set correctly (Z flag should be 0, N flag should be 0)
    if ((cpu.getFlags() & 0x40000000) == 0 && (cpu.getFlags() & 0x80000000) == 0) {
        std::cout << "CMN instruction test passed." << std::endl;
    } else {
        std::cout << "CMN instruction test failed." << std::endl;
    }
}
