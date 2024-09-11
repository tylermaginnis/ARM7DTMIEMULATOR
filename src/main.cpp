#include <iostream>
#include <string>
#include "cpu.h"
#include "../include/test/test.h"

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
        }
    }

    return 0;
}