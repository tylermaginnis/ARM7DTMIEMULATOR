#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "ARM/arm_instructions_MOV.h"

enum class Field {
    CONTROL,
    FLAGS,
    SPSR,
    CPSR
};

enum class Condition {
    EQ, // Equal
    NE, // Not equal
    CS, // Carry set/unsigned higher or same
    CC, // Carry clear/unsigned lower
    MI, // Minus/negative
    PL, // Plus/positive or zero
    VS, // Overflow
    VC, // No overflow
    HI, // Unsigned higher
    LS, // Unsigned lower or same
    GE, // Signed greater than or equal
    LT, // Signed less than
    GT, // Signed greater than
    LE, // Signed less than or equal
    AL  // Always
};

class CPU {
public:
    void setRegister(uint32_t reg, uint32_t value);
    uint32_t getRegister(uint32_t reg);
    uint32_t getSPSR();
    uint32_t getCPSR();
    void setSPSR(Field field, uint32_t value);
    void setCPSR(Field field, uint32_t value);
    bool checkCondition(Condition cond);
    void updateFlags(uint32_t result);
    void setCPSRControl(uint32_t value);
    void setCPSRFlags(uint32_t value);
    void setSPSRControl(uint32_t value);
    void setSPSRFlags(uint32_t value);

private:
    uint32_t registers[16]; // Assuming 16 general-purpose registers
    uint32_t spsr;
    uint32_t cpsr;
};

#endif // CPU_H