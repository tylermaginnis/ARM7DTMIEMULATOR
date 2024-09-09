#ifndef ARM_INSTRUCTIONS_MOV_H
#define ARM_INSTRUCTIONS_MOV_H

#include "../cpu.h"

void executeMOV(class CPU& cpu, uint32_t instruction);
void executeMVN(class CPU& cpu, uint32_t instruction);
void executeMRS(class CPU& cpu, uint32_t instruction);
void executeMSR(class CPU& cpu, uint32_t instruction);


#endif // ARM_INSTRUCTIONS_MOV_H