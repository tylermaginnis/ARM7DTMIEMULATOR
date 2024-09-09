# ARM7TDMI Emulator

This project is an emulator for the ARM7TDMI processor, written in C++. It includes implementations for various ARM instructions and a simple CPU model.

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

## Test Cases

| Test Case                | Description                                      | Result       |
|--------------------------|--------------------------------------------------|--------------|
| `testMOV`                | Tests the MOV instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMVN`                | Tests the MVN instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMRS`                | Tests the MRS instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMSR`                | Tests the MSR instruction                        | <span style="background-color: #90EE90 !important;">Passed</span> |
| `testMSRImmediate`       | Tests the MSRImmediate instruction               | <span style="background-color: #90EE90 !important;">Passed</span> |

### Analysis of Test Results

The following analysis is based on the output of the command-line interface (CLI) for each test case:

#### MOV Instruction Test
- **Instruction**: `e3a01001`
- **Condition**: Always (e)
- **S bit**: 0
- **Destination Register (Rd)**: 1
- **Operand2 (Oprnd2)**: 1
- **Condition Check**: Passed
- **Register Update**: Register 1 set to 1
- **Result**: Test passed

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

### Running the Emulator

To run the emulator, execute the following command from the build directory:
