#ifndef MOV_INSTRUCTION_H
#define MOV_INSTRUCTION_H

#include "../ARMinstruction.h"

class MOVInstruction : public ARMInstruction {
public:
    void execute(CPU& cpu, uint32_t instruction) override;
};

#endif // MOV_INSTRUCTION_H