# write_instructions.py
ARM_MOV_instructions = [
    0xE1A01002,  # MOV R1, R0, LSL #2
    0xE3A02001   # MOV R2, #1
]

with open("../src/test/ARM/MOV/arm7dtmi_test_MOV.bin", "wb") as f:
    for instruction in ARM_MOV_instructions:
        f.write(instruction.to_bytes(4, byteorder='little'))