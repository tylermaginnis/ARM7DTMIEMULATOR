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


### Running the Emulator

To run the emulator, execute the following command from the build directory:
