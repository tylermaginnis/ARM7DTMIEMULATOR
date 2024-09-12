#ifndef ARM_INSTRUCTION_H
#define ARM_INSTRUCTION_H

#include "../../cpu.h"

class ARMInstruction {
public:
    virtual void execute(CPU& cpu, uint32_t instruction) = 0;
    virtual ~ARMInstruction() = default;
};

#endif // ARM_INSTRUCTION_H