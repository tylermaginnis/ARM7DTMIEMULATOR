#ifndef TEST_ARITHMETIC_H
#define TEST_ARITHMETIC_H

#include "../../cpu.h"

// ARITHMETIC tests
void testADD(CPU& cpu);
void testADC(CPU& cpu);
void testSUB(CPU& cpu);
void testSBC(CPU& cpu);
void testRSB(CPU& cpu);
void testRSC(CPU& cpu);
void testMUL(CPU& cpu);
void testMLA(CPU& cpu);
void testUMULL(CPU& cpu);
void testUMLAL(CPU& cpu);
void testSMULL(CPU& cpu);
void testSMLAL(CPU& cpu);
void testCMP(CPU& cpu);
void testCMN(CPU& cpu);

#endif // TEST_ARITHMETIC_H