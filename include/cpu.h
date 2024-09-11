#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "ARM/arm_instructions_MOV.h"
#include "ARM/arm_instructions_ARITHMETIC.h"

enum class Field {
    CONTROL,
    FLAGS,
    SPSR,
    CPSR,
    ALL,
    INVALID
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

enum class Mode {
    USER,
    FIQ,
    IRQ,
    SUPERVISOR,
    ABORT,
    UNDEFINED,
    SYSTEM
};

class CPU {
public:
    void resetCPU();
    void setRegister(uint32_t reg, uint32_t value);
    uint32_t getRegister(uint32_t reg);
    uint32_t getSPSR();
    uint32_t getCPSR();
    void setSPSR(uint32_t field, uint32_t value);
    void setCPSR(uint32_t field, uint32_t value);
    void handleImmediateValue(uint32_t& registerValue, uint32_t immediateValue, uint32_t fieldMask, bool isCPSR);
    bool checkCondition(Condition cond);
    void updateFlags(uint32_t result);
    void setCPSRControl(uint32_t value);
    void setCPSRFlags(uint32_t value);
    void setSPSRControl(uint32_t value);
    void setSPSRFlags(uint32_t value);
    void switchMode(Mode mode);
    uint32_t getFlags() const;


private:
    uint32_t registers[16]; // R0-R15
    uint32_t cpsr;          // Current Program Status Register
    uint32_t spsr;          // Saved Program Status Register

    // Banked registers
    uint32_t banked_r8_fiq;
    uint32_t banked_r9_fiq;
    uint32_t banked_r10_fiq;
    uint32_t banked_r11_fiq;
    uint32_t banked_r12_fiq;
    uint32_t banked_r13_fiq;
    uint32_t banked_r14_fiq;

    uint32_t banked_r13_irq;
    uint32_t banked_r14_irq;

    uint32_t banked_r13_svc;
    uint32_t banked_r14_svc;

    uint32_t banked_r13_abt;
    uint32_t banked_r14_abt;

    uint32_t banked_r13_und;
    uint32_t banked_r14_und;

    

    Mode currentMode;
};

#endif // CPU_H