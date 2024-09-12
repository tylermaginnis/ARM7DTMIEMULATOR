#ifndef TEST_MOV_H
#define TEST_MOV_H

#include "../../cpu.h"

// MOV tests
void testMOV(CPU& cpu);
void testMVN(CPU& cpu); 
void testMRS(CPU& cpu);
void testMSR(CPU& cpu);
void testMSRImmediate(CPU& cpu);

#endif // TEST_MOV_H