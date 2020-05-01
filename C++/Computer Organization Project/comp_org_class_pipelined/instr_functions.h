#ifndef INSTR_FUNCTIONS_H
#define INSTR_FUNCTIONS_H

#include <string>
#include "asm_binary.h"

using namespace std;

// Function prototypes
// 
string FETCH(string);
void DECODE(string, string &, string &, string &, string &, RegisterFile &, AsmBinary &);
void EXECUTE(string, string &, string &, string, AsmBinary &, DataMemory &, Clock &);
void MEMORY(string &, AsmBinary &, DataMemory &, bool, bool, bool);
void WRITE(string, RegisterFile &, AsmBinary &);

void SET(string &, AsmBinary &, Clock &); // Sets a #value into a register
void LOAD(string &, string, AsmBinary &, DataMemory &, Clock &);       // Loads from memory to register
void STORE(string, string &, AsmBinary &, DataMemory &, Clock &);       // Stores from register into memory
void MOVE(string &, string &, AsmBinary &, Clock &); // Moves the value of a register into another
void ADD(string &, string, string, AsmBinary &, Clock &); // Adds two registers and sets the value equal to another register
void SUBTRACT(string &, string, string, AsmBinary &, Clock &); // Subtracts two registers and sets the value equal to another register
void NEGATE(string &, string &, AsmBinary &, Clock &);
void MULTIPLY(string &, string, string, AsmBinary &, Clock &);
void DIVIDE(string &, string, string, AsmBinary &, Clock &);
void FLOOR(string &, string, AsmBinary &, Clock &);
void CEIL(string &, string, AsmBinary &, Clock &);
void ROUND(string &, string, AsmBinary &, Clock &);
void ABS(string &, string, AsmBinary &, Clock &);
void MIN(string &, string, string, AsmBinary &, Clock &);
void MAX(string &, string, string, AsmBinary &, Clock &);
void POWER(string &, string, AsmBinary &, Clock &);
void EXPONENT(string &, string, AsmBinary &, Clock &);
void SQUARE_ROOT(string &, string, AsmBinary &, Clock &);
void BRANCH(AsmBinary &, Clock &);
void BRANCH_NEGATIVE(string, AsmBinary &, Clock &);
void BRANCH_ZERO(string, AsmBinary &, Clock &);
void NO_OPERATION(Clock &);
void HALT();


#endif