#include "../../include/ARM/arm_instructions_ARITHMETIC.h"
#include <iostream>
#include <string>

void executeADD(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rn, and Oprnd2 from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute ADD
    uint32_t result = cpu.getRegister(Rn) + Oprnd2;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}


void executeADC(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rn, and shifter_operand from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t shifter_operand = instruction & 0xFFF; // This should be processed as a shifter operand

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Shifter Operand: " << shifter_operand << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Get the carry flag from CPSR
    uint32_t cpsr = cpu.getCPSR();
    std::cout << "Fetching CPSR for carry flag" << std::endl;
    std::cout << "CPSR: " << std::hex << cpsr << std::endl;
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    std::cout << "Carry flag: " << carry << std::endl;

    // Process shifter_operand
    uint32_t Rm = shifter_operand & 0xF;
    uint32_t shift_type = (shifter_operand >> 5) & 0x3;
    uint32_t shift_amount = (shifter_operand >> 7) & 0x1F;

    uint32_t operand2 = cpu.getRegister(Rm);
    switch (shift_type) {
        case 0: // Logical shift left
            operand2 <<= shift_amount;
            break;
        case 1: // Logical shift right
            operand2 >>= shift_amount;
            break;
        case 2: // Arithmetic shift right
            operand2 = static_cast<int32_t>(operand2) >> shift_amount;
            break;
        case 3: // Rotate right
            operand2 = (operand2 >> shift_amount) | (operand2 << (32 - shift_amount));
            break;
    }

    // Execute ADC
    uint32_t result = cpu.getRegister(Rn) + operand2 + carry;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeSUB(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t result = cpu.getRegister(Rn) - Oprnd2;
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeSBC(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF; // Extract Rm as the register operand

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Rm: " << Rm << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t cpsr = cpu.getCPSR();
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    uint32_t result = cpu.getRegister(Rn) - cpu.getRegister(Rm) - (1 - carry);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeRSB(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t result = Oprnd2 - cpu.getRegister(Rn);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeRSC(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 12) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t cpsr = cpu.getCPSR();
    uint32_t carry = (cpsr & 0x20000000) ? 1 : 0;
    uint32_t result = Oprnd2 - cpu.getRegister(Rn) - (1 - carry);
    cpu.setRegister(Rd, result);

    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeMUL(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rm, and Rs from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute MUL
    uint32_t result = cpu.getRegister(Rm) * cpu.getRegister(Rs);
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << result << std::endl;
}

void executeMLA(CPU& cpu, uint32_t instruction) {
    // Extract condition, S bit, Rd, Rm, Rs, and Rn from the instruction
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t Rd = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;
    uint32_t Rn = (instruction >> 12) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "Rd: " << Rd << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;
    std::cout << "Rn: " << Rn << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Fetch register values
    uint32_t Rm_val = cpu.getRegister(Rm);
    uint32_t Rs_val = cpu.getRegister(Rs);
    uint32_t Rn_val = cpu.getRegister(Rn);

    // Debug prints for register values
    std::cout << "Rm value: " << std::dec << Rm_val << std::endl;
    std::cout << "Rs value: " << std::dec << Rs_val << std::endl;
    std::cout << "Rn value: " << std::dec << Rn_val << std::endl;

    // Execute MLA
    uint32_t intermediate_result = Rm_val * Rs_val;
    uint32_t result = intermediate_result + Rn_val;
    std::cout << "Intermediate result (Rm_val * Rs_val): " << std::dec << intermediate_result << std::endl;
    std::cout << "Final result (intermediate_result + Rn_val): " << std::dec << result << std::endl;
    cpu.setRegister(Rd, result);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(result);
        std::cout << "Flags updated with " << result << std::endl;
    }

    // Debug print
    std::cout << "Register " << Rd << " set to " << std::dec << result << std::endl;
}

void executeUMULL(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t RdLo = (instruction >> 12) & 0xF;
    uint32_t RdHi = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "RdLo: " << RdLo << std::endl;
    std::cout << "RdHi: " << RdHi << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t Rm_val = cpu.getRegister(Rm);
    uint32_t Rs_val = cpu.getRegister(Rs);
    std::cout << "Rm value: " << Rm_val << ", Rs value: " << Rs_val << std::endl;

    uint64_t result = static_cast<uint64_t>(Rm_val) * static_cast<uint64_t>(Rs_val);
    uint32_t resultLo = static_cast<uint32_t>(result & 0xFFFFFFFF);
    uint32_t resultHi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF);

    std::cout << "Result: " << std::hex << result << std::endl;
    std::cout << "ResultLo: " << std::hex << resultLo << std::endl;
    std::cout << "ResultHi: " << std::hex << resultHi << std::endl;

    cpu.setRegister(RdLo, resultLo);
    std::cout << "Register " << RdLo << " set to " << std::hex << resultLo << std::endl;
    cpu.setRegister(RdHi, resultHi);
    std::cout << "Register " << RdHi << " set to " << std::hex << resultHi << std::endl;

    if (S) {
        cpu.updateFlags(resultLo);
        std::cout << "Flags updated with " << std::hex << resultLo << std::endl;
    }
}


void executeUMLAL(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t RdLo = (instruction >> 12) & 0xF;
    uint32_t RdHi = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "RdLo: " << RdLo << std::endl;
    std::cout << "RdHi: " << RdHi << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    uint32_t Rm_val = cpu.getRegister(Rm);
    uint32_t Rs_val = cpu.getRegister(Rs);
    uint64_t Rd_val = (static_cast<uint64_t>(cpu.getRegister(RdHi)) << 32) | cpu.getRegister(RdLo);
    std::cout << "Rm value: " << Rm_val << ", Rs value: " << Rs_val << std::endl;
    std::cout << "RdLo initial value: " << cpu.getRegister(RdLo) << std::endl;
    std::cout << "RdHi initial value: " << cpu.getRegister(RdHi) << std::endl;
    std::cout << "Combined Rd value: " << Rd_val << std::endl;

    uint64_t result = static_cast<uint64_t>(Rm_val) * static_cast<uint64_t>(Rs_val) + Rd_val;
    uint32_t resultLo = static_cast<uint32_t>(result & 0xFFFFFFFF);
    uint32_t resultHi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF);

    std::cout << "Multiplication result: " << std::hex << (static_cast<uint64_t>(Rm_val) * static_cast<uint64_t>(Rs_val)) << std::endl;
    std::cout << "Addition result: " << std::hex << result << std::endl;
    std::cout << "ResultLo: " << std::hex << resultLo << std::endl;
    std::cout << "ResultHi: " << std::hex << resultHi << std::endl;

    cpu.setRegister(RdLo, resultLo);
    std::cout << "Register " << RdLo << " set to " << std::hex << resultLo << std::endl;
    cpu.setRegister(RdHi, resultHi);
    std::cout << "Register " << RdHi << " set to " << std::hex << resultHi << std::endl;

    if (S) {
        cpu.updateFlags(resultLo);
        std::cout << "Flags updated with " << std::hex << resultLo << std::endl;
    }
}

void executeSMULL(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t RdLo = (instruction >> 12) & 0xF;
    uint32_t RdHi = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "RdLo: " << RdLo << std::endl;
    std::cout << "RdHi: " << RdHi << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute SMULL
    int64_t result = static_cast<int64_t>(static_cast<int32_t>(cpu.getRegister(Rm))) * static_cast<int64_t>(cpu.getRegister(Rs));
    uint32_t resultLo = static_cast<uint32_t>(result & 0xFFFFFFFF);
    uint32_t resultHi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF);

    cpu.setRegister(RdLo, resultLo);
    cpu.setRegister(RdHi, resultHi);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(resultLo);
        std::cout << "Flags updated with " << std::hex << resultLo << std::endl;
    }

    // Debug prints
    std::cout << "Result: " << std::hex << result << std::endl;
    std::cout << "ResultLo: " << std::hex << resultLo << std::endl;
    std::cout << "ResultHi: " << std::hex << resultHi << std::endl;
    std::cout << "Register " << RdLo << " set to " << std::hex << resultLo << std::endl;
    std::cout << "Register " << RdHi << " set to " << std::hex << resultHi << std::endl;
}

void executeSMLAL(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t S = (instruction >> 20) & 0x1;
    uint32_t RdLo = (instruction >> 12) & 0xF;
    uint32_t RdHi = (instruction >> 16) & 0xF;
    uint32_t Rm = instruction & 0xF;
    uint32_t Rs = (instruction >> 8) & 0xF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "S bit: " << S << std::endl;
    std::cout << "RdLo: " << RdLo << std::endl;
    std::cout << "RdHi: " << RdHi << std::endl;
    std::cout << "Rm: " << Rm << std::endl;
    std::cout << "Rs: " << Rs << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Fetch register values
    int32_t Rm_val = static_cast<int32_t>(cpu.getRegister(Rm));
    int32_t Rs_val = static_cast<int32_t>(cpu.getRegister(Rs));
    int64_t Rd_val = (static_cast<int64_t>(cpu.getRegister(RdHi)) << 32) | cpu.getRegister(RdLo);

    // Debug prints for register values
    std::cout << "Rm value: " << Rm_val << std::endl;
    std::cout << "Rs value: " << Rs_val << std::endl;
    std::cout << "RdLo initial value: " << cpu.getRegister(RdLo) << std::endl;
    std::cout << "RdHi initial value: " << cpu.getRegister(RdHi) << std::endl;
    std::cout << "Combined Rd value: " << Rd_val << std::endl;

    // Execute SMLAL
    int64_t result = static_cast<int64_t>(Rm_val) * static_cast<int64_t>(Rs_val) + Rd_val;
    uint32_t resultLo = static_cast<uint32_t>(result & 0xFFFFFFFF);
    uint32_t resultHi = static_cast<uint32_t>((result >> 32) & 0xFFFFFFFF);

    // Debug prints for results
    std::cout << "Multiplication result: " << (static_cast<int64_t>(Rm_val) * static_cast<int64_t>(Rs_val)) << std::endl;
    std::cout << "Addition result: " << result << std::endl;
    std::cout << "ResultLo: " << resultLo << std::endl;
    std::cout << "ResultHi: " << resultHi << std::endl;

    // Set the result in the destination registers
    cpu.setRegister(RdLo, resultLo);
    cpu.setRegister(RdHi, resultHi);

    // Update flags if S bit is set
    if (S) {
        cpu.updateFlags(resultLo);
        std::cout << "Flags updated with " << resultLo << std::endl;
    }

    // Debug prints for final register values
    std::cout << "Register " << RdLo << " set to " << resultLo << std::endl;
    std::cout << "Register " << RdHi << " set to " << resultHi << std::endl;
}

void executeCMP(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute CMP (subtract Oprnd2 from Rn and update flags)
    uint32_t Rn_val = cpu.getRegister(Rn);
    uint32_t result = Rn_val - Oprnd2;

    // Update flags
    cpu.updateFlags(result);

    // Debug prints
    std::cout << "Rn value: " << Rn_val << std::endl;
    std::cout << "Result: " << result << std::endl;
    std::cout << "Flags updated with " << result << std::endl;
}

void executeCMN(CPU& cpu, uint32_t instruction) {
    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t Rn = (instruction >> 16) & 0xF;
    uint32_t Oprnd2 = instruction & 0xFFF;

    // Debug prints
    std::cout << "Instruction: " << std::hex << instruction << std::endl;
    std::cout << "Condition: " << cond << std::endl;
    std::cout << "Rn: " << Rn << std::endl;
    std::cout << "Oprnd2: " << Oprnd2 << std::endl;

    // Check condition
    if (!cpu.checkCondition(static_cast<Condition>(cond))) {
        std::cout << "Condition failed, do not execute" << std::endl;
        return;
    }

    // Execute CMN (add Oprnd2 to Rn and update flags)
    uint32_t Rn_val = cpu.getRegister(Rn);
    uint32_t result = Rn_val + Oprnd2;

    // Update flags
    cpu.updateFlags(result);

    // Debug prints
    std::cout << "Rn value: " << Rn_val << std::endl;
    std::cout << "Result: " << result << std::endl;
    std::cout << "Flags updated with " << result << std::endl;
}