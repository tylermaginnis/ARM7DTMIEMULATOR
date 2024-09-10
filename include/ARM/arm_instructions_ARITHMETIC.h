#ifndef ARM_INSTRUCTIONS_ARITHMETIC_H
#define ARM_INSTRUCTIONS_ARITHMETIC_H

#include "../cpu.h" // For the CPU class

void executeADD(class CPU& cpu, uint32_t instruction);
void executeADC(class CPU& cpu, uint32_t instruction);

#endif // ARM_INSTRUCTIONS_ARITHMETIC_H