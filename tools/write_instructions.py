# write_instructions.py
ARM_MOV_instructions = [
    0xE3B0F001,  # Example MOV instruction: MOV R15, #1 (S bit set)
    0xE3B01001,  # Example MOV instruction: MOV R1, #1 (S bit set)
    0xE1A01001,  # Example MOV instruction: MOV R1, R1 (S bit not set)
    0x03A01001   # Example MOV instruction: MOV R1, #1 (Condition fails)
]

with open("../src/test/ARM/MOV/arm7tdmi_test_MOV.bin", "wb") as f:
    for instruction in ARM_MOV_instructions:
        f.write(instruction.to_bytes(4, byteorder='little'))