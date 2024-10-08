#ifndef ARM_INSTRUCTIONS_ARITHMETIC_H
#define ARM_INSTRUCTIONS_ARITHMETIC_H

#include "../cpu.h" // For the CPU class

void executeADD(class CPU& cpu, uint32_t instruction);
void executeADC(class CPU& cpu, uint32_t instruction);
void executeSUB(class CPU& cpu, uint32_t instruction);
void executeSBC(class CPU& cpu, uint32_t instruction);
void executeRSB(class CPU& cpu, uint32_t instruction);
void executeRSC(class CPU& cpu, uint32_t instruction);
void executeMUL(class CPU& cpu, uint32_t instruction);
void executeMLA(class CPU& cpu, uint32_t instruction);
void executeUMULL(class CPU& cpu, uint32_t instruction);
void executeUMLAL(class CPU& cpu, uint32_t instruction);
void executeSMULL(class CPU& cpu, uint32_t instruction);
void executeSMLAL(class CPU& cpu, uint32_t instruction);
void executeCMP(class CPU& cpu, uint32_t instruction);
void executeCMN(class CPU& cpu, uint32_t instruction);

#endif // ARM_INSTRUCTIONS_ARITHMETIC_H