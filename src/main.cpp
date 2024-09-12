#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/test/test.h"
#include "../include/instructions/ARM/ARMinstruction.h"
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    CPU cpu; // Create a single CPU instance

    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "test") {
            // MOV tests
            testMOV(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMVN(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMRS(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMSR(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMSRImmediate(cpu);
            std::cout << "-----------------------------------------" << std::endl;

            // ARITHMETIC tests
            testADD(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testADC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSUB(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSBC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testRSB(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testRSC(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMUL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testMLA(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testUMULL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testUMLAL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSMULL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testSMLAL(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testCMP(cpu);
            std::cout << "-----------------------------------------" << std::endl;
            testCMN(cpu);
            std::cout << "-----------------------------------------" << std::endl;
        } else if (arg == "test bin") {
            std::string filePath = "C:\\dev\\ARM7TDMIEmulator\\src\\test\\ARM\\MOV\\arm7tdmi_test_MOV.bin";
            std::cout << "Attempting to open the binary file: " << filePath << std::endl;
            std::ifstream file(filePath, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Failed to open the binary file: " << filePath << std::endl;
                return 1;
            } else {
                std::cout << "Successfully opened the binary file: " << filePath << std::endl;
            }

            // Read the binary file into a buffer
            std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
            std::cout << "Buffer size: " << buffer.size() << std::endl;
            // Process the buffer as needed
            // Each instruction is 4 bytes, so we need to read 4 bytes at a time
            for (size_t i = 0; i < buffer.size(); i += 4) {
                uint32_t instruction = buffer[i] |
                                       (buffer[i + 1] << 8) |
                                       (buffer[i + 2] << 16) |
                                       (buffer[i + 3] << 24);
                cpu.executeInstruction(instruction);
            }

            file.close();
        }
    }

    return 0;
}