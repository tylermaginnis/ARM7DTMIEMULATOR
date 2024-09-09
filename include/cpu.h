#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "ARM/arm_instructions_MOV.h"

enum class Field {
    SPSR
};

enum class Condition {
    // Define the conditions here
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

private:
    uint32_t registers[16]; // Assuming 16 general-purpose registers
    uint32_t spsr;
    uint32_t cpsr;
};

#endif // CPU_H