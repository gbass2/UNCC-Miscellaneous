#ifndef INSTR_FUNCTIONS_H
#define INSTR_FUNCTIONS_H

#include <string>
#include "asm_binary.h"

using namespace std;

// Function prototypes
// 
string FETCH(string);
void DECODE(string, string &, string &, string &, string &, RegisterFile &, AsmBinary &);
void EXECUTE(string, string &, string &, string, AsmBinary &);
void MEMORY(string &, AsmBinary &, DataMemory &);
void WRITE(string, RegisterFile &, AsmBinary &);

void SET(string &, AsmBinary &); // Sets a #value into a register
void LOAD(string &, string, AsmBinary &);       // Loads from memory to register
void STORE(string, string &, AsmBinary &asmToBin);       // Stores from register into memory
void MOVE(string &, string &, AsmBinary &); // Moves the value of a register into another
void ADD(string &, string, string, AsmBinary &); // Adds two registers and sets the value equal to another register
void SUBTRACT(string &, string, string, AsmBinary &); // Subtracts two registers and sets the value equal to another register
void NEGATE(string &, string &, AsmBinary &);
void MULTIPLY(string &, string, string, AsmBinary &);
void DIVIDE(string &, string, string, AsmBinary &);
void FLOOR(string &, string, AsmBinary &);
void CEIL(string &, string, AsmBinary &);
void ROUND(string &, string, AsmBinary &);
void ABS(string &, string, AsmBinary &);
void MIN(string &, string, string, AsmBinary &);
void MAX(string &, string, string, AsmBinary &);
void POWER(string &, string, AsmBinary &);
void EXPONENT(string &, string, AsmBinary &);
void SQUARE_ROOT(string &, string, AsmBinary &);
void BRANCH(AsmBinary &);
void BRANCH_NEGATIVE(string, AsmBinary &);
void BRANCH_ZERO(string, AsmBinary &);
void NO_OPERATION();
void HALT();


#endif