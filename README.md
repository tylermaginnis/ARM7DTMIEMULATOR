# ARM7TDMI Emulator

This project is an emulator for the ARM7TDMI processor, written in C++. It includes implementations for various ARM instructions and a CPU model.

## Features

- Emulates ARM7TDMI processor

## Getting Started

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/ARM7TDMI.git
    cd ARM7TDMI
    ```

2. Create a build directory and navigate to it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    cmake --build .
    ```

5. To run the tests, use the following command:
    ```sh
    ./ARM7TDMI test
    ```

This will execute a series of predefined tests to ensure the emulator is functioning correctly.

## Code Structure

- `src/main.cpp`: Contains the main function and test functions.
- `src/ARM/ARM_instructions_MOV.cpp`: Implements the MOV, MVN, MRS, MSR, and MSRImmediate instructions.
- `src/cpu.cpp`: Implements the CPU class and its methods.
- `include/ARM/arm_instructions_MOV.h`: Header file for ARM instruction implementations.
- `include/cpu.h`: Header file for the CPU class.

## Glossary of ARM7TDMI Terminology

- **MOV**: Move - Transfers a value from one register to another or loads an immediate value into a register.
- **MVN**: Move Not - Transfers the bitwise NOT of an immediate value or a register value into a destination register.
- **MRS**: Move PSR to Register - Transfers the value of the CPSR or SPSR to a general-purpose register.
- **MSR**: Move Register to PSR - Transfers a value from a general-purpose register to the CPSR or SPSR.
- **MSRImmediate**: Move Immediate to PSR - Transfers an immediate value to the CPSR or SPSR.
- **CPSR**: Current Program Status Register - Holds the current state of the processor, including condition flags, interrupt status, and processor mode.
- **SPSR**: Saved Program Status Register - Holds the saved state of the CPSR when an exception occurs, allowing the processor to return to its previous state after handling the exception.
- **ADD**: Add - Adds two registers or a register and an immediate value, and stores the result in a destination register.
- **ADC**: Add with Carry - Adds two registers or a register and an immediate value, including the carry flag, and stores the result in a destination register.
- **SUB**: Subtract - Subtracts two registers or a register and an immediate value, and stores the result in a destination register.
- **SBC**: Subtract with Carry - Subtracts two registers or a register and an immediate value, including the carry flag, and stores the result in a destination register.
- **RSB**: Reverse Subtract - Subtracts a register from another register, and stores the result in a destination register.
- **RSC**: Reverse Subtract with Carry - Subtracts a register from another register, including the carry flag, and stores the result in a destination register.
- **MUL**: Multiply - Multiplies two registers and stores the result in a destination register.
- **MLA**: Multiply and Add - Multiplies two registers, adds a third register, and stores the result in a destination register.
- **UMULL**: Unsigned Multiply Long - Multiplies two registers and stores the 64-bit result in two consecutive registers.
- **UMLAL**: Unsigned Multiply Long Accumulate - Multiplies two registers, adds the result to a third register, and stores the 64-bit result in two consecutive registers.

## MOV Test Cases

| Test Case                | Description                                      | Result       |
|--------------------------|--------------------------------------------------|--------------|
| `testMOV`                | Tests the MOV instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMVN`                | Tests the MVN instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMRS`                | Tests the MRS instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMSR`                | Tests the MSR instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMSRImmediate`       | Tests the MSRImmediate instruction               | <span style="background-color: #90EE90 !important;">Passed</span> |


### Analysis of Test Results

The following analysis is based on the output of the command-line interface (CLI) for each test case:

<table>
  <tr>
    <td>
      <ul>
        <li><strong>Instruction</strong>: `e3a01001`</li>
        <li><strong>Condition</strong>: Always (e)</li>
        <li><strong>S bit</strong>: 0</li>
        <li><strong>Destination Register (Rd)</strong>: 1</li>
        <li><strong>Operand2 (Oprnd2)</strong>: 1</li>
        <li><strong>Condition Check</strong>: Passed</li>
        <li><strong>Register Update</strong>: Register 1 set to 1</li>
        <li><strong>Result</strong>: Test passed</li>
      </ul>
    </td>
    <td>
      <p align="center">
        <img src="docs/diagrams/MOV/result/MOV.svg" alt="MOV Instruction Test" />
      </p>
    </td>
  </tr>
</table>

#### MVN Instruction Test
- **Instruction**: `e3e01001`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Operand2 (Oprnd2)**: 1
- **Condition Check**: Passed
- **Register Update**: Register 1 set to `0xfffffffe` (bitwise NOT of 1)
- **Result**: Test passed

#### MRS Instruction Test (CPSR)
- **Instruction**: `e10f0000`
- **Condition**: Always (e)
- **Destination Register (Rd)**: 0
- **PSR**: CPSR (0)
- **Condition Check**: Passed
- **Register Update**: Register 0 set to the value of CPSR (`0x87654321`)
- **Result**: Test passed

#### MRS Instruction Test (SPSR)
- **Instruction**: `e14f0000`
- **Condition**: Always (e)
- **Destination Register (Rd)**: 0
- **PSR**: SPSR (1)
- **Condition Check**: Passed
- **Register Update**: Register 0 set to the value of SPSR (`0x12345678`)
- **Result**: Test passed

#### MSR Instruction Test (CPSR)
- **Instruction**: `e129f001`
- **Condition**: Always (e)
- **Field Mask**: 9
- **PSR**: CPSR (0)
- **Source Register (Rm)**: 1
- **Condition Check**: Passed
- **Register Update**: CPSR set to the value of Register 1 (`0x87654321`)
- **Result**: Test passed

#### MSR Instruction Test (SPSR)
- **Instruction**: `e169f002`
- **Condition**: Always (e)
- **Field Mask**: 9
- **PSR**: SPSR (1)
- **Source Register (Rm)**: 2
- **Condition Check**: Passed
- **Register Update**: SPSR set to the value of Register 2 (`0x12345678`)
- **Result**: Test passed

#### MSR Immediate Instruction Test (CPSR)
- **Instruction**: `e32ef001`
- **Condition**: Always (e)
- **Field Mask**: e
- **PSR**: CPSR (0)
- **Immediate Value**: 1
- **Rotate**: 0
- **Condition Check**: Passed
- **Register Update**: CPSR set to `0x17000021` after handling the immediate value
- **Result**: Test passed

#### MSR Immediate Instruction Test (SPSR)
- **Instruction**: `e36ef002`
- **Condition**: Always (e)
- **Field Mask**: e
- **PSR**: SPSR (1)
- **Immediate Value**: 2
- **Rotate**: 0
- **Condition Check**: Passed
- **Register Update**: SPSR set to `0x22000078` after handling the immediate value
- **Result**: Test passed

Overall, all the tests for the MOV, MVN, MRS, MSR, and MSRImmediate instructions have passed successfully, indicating that the emulator is functioning correctly for these instructions.

## ARITHMETIC Test Cases

| Test Case                | Description                                      | Result       |
|--------------------------|--------------------------------------------------|--------------|
| `testADD`                | Tests the ADD instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testADC`                | Tests the ADC instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testSUB`                | Tests the SUB instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testSBC`                | Tests the SBC instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testRSB`                | Tests the RSB instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testRSC`                | Tests the RSC instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMUL`                | Tests the MUL instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMLA`                | Tests the MLA instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testUMULL`              | Tests the UMULL instruction                      | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testUMLAL`              | Tests the UMLAL instruction                      | <span style="background-color: #90EE90 !important;">Passed</span> |


#### ADD Instruction Test
- **Instruction**: `e2811003`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Operand2**: 3
- **Condition Check**: Passed
- **Register Update**: Register 1 set to 8 (`5 + 3`)
- **Result**: Test passed

#### ADC Instruction Test
- **Instruction**: `e0a11002`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Source Register (Rm)**: 2
- **Condition Check**: Passed
- **Carry Flag**: 1
- **Register Update**: Register 1 set to 9 (`5 + 3 + 1`)
- **Result**: Test passed

#### SUB Instruction Test
- **Instruction**: `e2411003`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Operand2**: 3
- **Condition Check**: Passed
- **Register Update**: Register 1 set to 7 (`10 - 3`)
- **Result**: Test passed

#### SBC Instruction Test
- **Instruction**: `e0c11002`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Source Register (Rm)**: 2
- **Condition Check**: Passed
- **Carry Flag**: 1
- **Register Update**: Register 1 set to 7 (`10 - 3 - (1 - 1)`)
- **Result**: Test passed

#### RSB Instruction Test
- **Instruction**: `e2611003`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Operand2**: 3
- **Condition Check**: Passed
- **Register Update**: Register 1 set to -2 (`3 - 5`)
- **Result**: Test passed

#### RSC Instruction Test
- **Instruction**: `e0e11002`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rn)**: 1
- **Source Register (Rm)**: 2
- **Condition Check**: Passed
- **Carry Flag**: 1
- **Register Update**: Register 1 set to -3 (`2 - 5 - (1 - 1)`)
- **Result**: Test passed

#### MUL Instruction Test
- **Instruction**: `e0010291`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rm)**: 1
- **Source Register (Rs)**: 2
- **Condition Check**: Passed
- **Register Update**: Register 1 set to 15 (`5 * 3`)
- **Result**: Test passed

#### MLA Instruction Test
- **Instruction**: `e0211392`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Source Register (Rm)**: 2
- **Source Register (Rs)**: 3
- **Source Register (Rn)**: 1
- **Condition Check**: Passed
- **Register Update**: Register 1 set to 35 (`5 * 3 + 10`)
- **Result**: Test passed

#### UMULL Instruction Test
- **Instruction**: `e0830493`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register Low (RdLo)**: 0
- **Destination Register High (RdHi)**: 3
- **Source Register (Rm)**: 3
- **Source Register (Rs)**: 4
- **Condition Check**: Passed
- **Register Update**: Register 0 set to `0xFFFFFFF8`, Register 3 set to `0x7`
- **Result**: Test passed

#### UMLAL Instruction Test
- **Instruction**: `e0e12392`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register Low (RdLo)**: 2
- **Destination Register High (RdHi)**: 1
- **Source Register (Rm)**: 2
- **Source Register (Rs)**: 3
- **Condition Check**: Passed
- **Register Update**: Register 2 set to `0xDB97530E`, Register 1 set to `0x12345677`
- **Result**: Test passed



Overall, all the tests for the ADD and ADC instructions have passed successfully, indicating that the emulator is functioning correctly for these arithmetic instructions.


### Running the Emulator

To run the emulator, execute the following command from the build directory:
