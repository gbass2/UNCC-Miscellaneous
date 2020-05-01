#include "instr_functions.h"
#include "asm_binary.h"
#include "number.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

// Fetching the instruction
string FETCH(string instruction){
    return instruction;
}

// Decoding the Instruction
void DECODE(string instruction, string& opcode, string& Ri, string& Rj, string& Rk, RegisterFile &registers, AsmBinary &asmToBin){
    // Breaking up the binary into opcode
    opcode = instruction.substr(0,8);
    
    // Setting the control signals depending on the incoming instruction
    if(opcode == "00011000"){
        // Setting the control signals 
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011001"){
        asmToBin.branch = 0;
        asmToBin.memRead = 1;
        asmToBin.memToReg = 1;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011010"){
        asmToBin.branch = 0;
        asmToBin.aluOp = 1;
        asmToBin.memWrite = 1;
    }
    else if(opcode == "00011011"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011100"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 0;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011101"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 0;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011110"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00011111"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 0;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100000"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 0;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100001"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100010"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100011"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100100"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100101"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100110"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00100111"){
        asmToBin.branch = 0;
        asmToBin.reg2Loc = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 1;
        asmToBin.regWrite = 1;
    }
    else if(opcode == "00101000"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 1;
        asmToBin.reg2Loc = 1;
    }
    else if(opcode == "00101001"){
        asmToBin.branch = 0;
        asmToBin.memToReg = 0;
        asmToBin.aluOp = 1;
        asmToBin.aluSrc = 1;
        asmToBin.reg2Loc = 1;
    }
    else if(opcode == "00101010"){
        asmToBin.branch = 1;
        asmToBin.regWrite = 0;
        asmToBin.memToReg = 0;
        asmToBin.memRead = 0;
        asmToBin.memWrite = 0;
    }
    else if(opcode == "00101011"){
        asmToBin.branch = 1;
        asmToBin.regWrite = 0;
        asmToBin.memToReg = 0;
        asmToBin.memRead = 0;
        asmToBin.memWrite = 0;
    }
    else if(opcode == "00101100"){
        asmToBin.branch = 1;
        asmToBin.regWrite = 0;
        asmToBin.memToReg = 0;
        asmToBin.memRead = 0;
        asmToBin.memWrite = 0;
    }
    else if(opcode == "00101101"){
        asmToBin.branch = 0;
        asmToBin.regWrite = 0;
        asmToBin.memToReg = 0;
        asmToBin.memRead = 0;
        asmToBin.memWrite = 0;
    }
    else if(opcode == "00101110"){
        asmToBin.branch = 0;
        asmToBin.regWrite = 0;
        asmToBin.memToReg = 0;
        asmToBin.memRead = 0;
        asmToBin.memWrite = 0;
    }
    
    // Braking up the binary into Ri, Rj, and Rk
    Ri = instruction.substr(8,8);
    Rj = instruction.substr(16,8);
    Rk = instruction.substr(24,8);
    
    bool resultRegPos = 0; // Used to determine the pos of Ri in the value vector
    
    // Getting the value for Rj and Rk
    if(Rj != "00000000" &&  opcode != "00011000" && asmToBin.branch != 1){
        resultRegPos = 0;
        Rj = registers.GET_VALUE(Rj, resultRegPos);
        
    }
    else if(Rj == "00000000" || asmToBin.branch == 1){
        Rj = "00000000000000000000000000000000";
    }
        
    if(asmToBin.reg2Loc == 0 && Rk != "00000000" && opcode != "00110000" && asmToBin.branch != 1){
        resultRegPos = 0;
        Rk = registers.GET_VALUE(Rk, resultRegPos);
        
    }else if(Rk == "00000000" || asmToBin.branch == 1)
        Rk = "00000000000000000000000000000000";
    
    if(Ri != "00000000"){
        resultRegPos = 1;
        Ri = registers.GET_VALUE(Ri, resultRegPos);
    }
    else if(Ri == "00000000")
        Ri = "00000000000000000000000000000000";
}

// Execute the instruction
void EXECUTE(string instructionString, string &R1, string &R2, string R3, AsmBinary& asmToBin, DataMemory & memory, Clock &clockTime){
    // This function using if else statment to call each instuction function by their binary opcode
    // R1(Ri), R2(Rj), R3(Rk) as three registers
    if(instructionString == "00011000"){
        SET(R1, asmToBin, clockTime); //Ri ← FPvalue
    }
    else if(instructionString == "00011001"){
        LOAD(R1,R2, asmToBin, memory, clockTime);  //Ri ← M[Rj]
    }
    else if(instructionString == "00011010"){
        STORE(R1,R2, asmToBin, memory, clockTime);  //M[Ri] ← Rj
    }
    else if(instructionString == "00011011"){
         MOVE(R1, R2, asmToBin, clockTime);  //Ri ← Rj
    }
    else if(instructionString == "00011100"){
        ADD(R1, R2, R3, asmToBin, clockTime);  //Ri ← Rj + Rk
    }
    else if(instructionString == "00011101"){
        SUBTRACT(R1, R2, R3, asmToBin, clockTime);  //Ri ← Rj - Rk
    }
    else if(instructionString == "00011110"){
        NEGATE(R1, R2, asmToBin, clockTime);  //Ri ← -Rj
    }
    else if(instructionString == "00011111"){
        MULTIPLY(R1, R2, R3, asmToBin, clockTime);  //Ri ← Rj * Ri
    }
    else if(instructionString == "00100000"){
        DIVIDE(R1, R2, R3, asmToBin, clockTime);  //Ri ← Rj / Ri	
    }
    else if(instructionString == "00100001"){
        FLOOR(R1, R2, asmToBin, clockTime);  //Ri ← ⌊Rj⌋
    }
    else if(instructionString == "00100010"){
        CEIL(R1, R2, asmToBin, clockTime);  //Ri ← ⌈Rj⌉
    }
    else if(instructionString == "00100011"){
        ROUND(R1, R2, asmToBin, clockTime);  //Ri ← round(Rj)
    }
    else if(instructionString == "00100100"){
        ABS(R1, R2, asmToBin, clockTime);  //Ri ← |Rj|
    }
    else if(instructionString == "00100101"){
        MIN(R1, R2, R3, asmToBin, clockTime);  //Ri ← min(Rj, Rk)
    }
    else if(instructionString == "00100110"){
        MAX(R1, R2, R3, asmToBin, clockTime);  //Ri ← max(Rj, Rk)
    }
    else if(instructionString == "00100111"){
        POWER(R1, R2, asmToBin, clockTime);  //Ri ← Rj^int
    }
    else if(instructionString == "00101000"){
        EXPONENT(R1, R2, asmToBin, clockTime);  //Ri ← e^Rj
    }
    else if(instructionString == "00101001"){
        SQUARE_ROOT(R1, R2, asmToBin, clockTime);  //Ri ← sqrt(Rj)
    }
    else if(instructionString == "00101010"){
        // Setting the control signals inside the function
        BRANCH(asmToBin, clockTime);  //PC ← M[Ri]
    }
    else if(instructionString == "00101011"){
        // Setting the control signals inside the function
        BRANCH_ZERO(R1, asmToBin, clockTime);  //If(Ri==0) PC ← LABEL(line)
    }
    else if(instructionString == "00101100"){
        // Setting the control signals inside the function
        BRANCH_NEGATIVE(R1, asmToBin, clockTime);  //If(Ri<0) PC ← LABEL(line)
    }
    else if(instructionString == "00101101"){
        NO_OPERATION(clockTime);  //No Op, wait
    }
    else if(instructionString == "00101110"){
        HALT();  //Stop Program
    }
}

// Getting the value form memory to be loaded if load is called and storing the value of Rj into memory
void MEMORY(string &Ri, AsmBinary &asmToBin, DataMemory &memory, bool memRead, bool memToReg, bool memWrite){
   if(memRead == 1 && memToReg == 1){
        if(!(memory.tempLocation).empty()){  //Rj memory location loaded
        }
            // Retrieving the forwarded value
            if(asmToBin.forwardA == 1){
                asmToBin.forwardValueA = Ri;
                asmToBin.forwardB = 0;
            }
            else if(asmToBin.forwardB == 1){
                asmToBin.forwardValueB = Ri;
                asmToBin.forwardA = 0;
            }
   }
    
    else if(memWrite == 1){
        (memory.memVal).push_back(Ri); // placing the value for Rj into memory.Not sure if this is correct
    }
}

// Writing the result of the operation back to the register Ri
void WRITE(string Ri, RegisterFile &registers, AsmBinary &asmToBin){
    
    // Forwarding the value form the write back stage if needed
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    else if(asmToBin.forwardB == 1){
        asmToBin.forwardB = 0;
        asmToBin.forwardValueB = Ri;
    }
    
    // Writing to the register
    registers.WRITE_VALUE(Ri);
}

// Below are the functions ALU operations

void SET(string &Ri, AsmBinary &asmToBin, Clock &clockTime){  //Set Ri with the immediate value
    cout << endl << "------SET------" << endl;
    
    string numberToSet; // The immediate value
    int it = 0; //iterator accessing immediate 
    size_t i = 0; // Iterator for the for loop that finds the immediate value
    
    // Accessing an immediate value if the aluSrc signal is a 1
    if(asmToBin.aluSrc == 1){
        // If no branching, then loop as normal. 
        // If branching, then set the staring location to the label(line) looped.
        if(asmToBin.tempBranch1 == true){
            if(asmToBin.iterator < 1){
                i = asmToBin.numberLocation - 1;
                asmToBin.iterator = 1;
            }else
                i = 0;
        }
        
        // Access the correct immediate value to set. 
        for(i; i < (asmToBin.number1Val).size(); i++){
            if((asmToBin.isConstantNumber1).at(i) == 1){
                numberToSet = (asmToBin.number1Val).at(i);
                break;
            }
        }
    }
    
    cout << "value in DEC: " << numberToSet << endl;
    
    Number convFP(numberToSet);
    
    // Converting the immediate value to floating poin to be set
    if(asmToBin.aluOp == 1)
        convFP.CONVERT_TO_FLOATING_POINT();
    
    // Returning the result to be written to the register in the write back stage
    Ri = convFP.GET_NUMBER();
    
    // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    
    // Removes the immediate value from the temperary variable after set in a register
    vector<string> temp1;
    vector<bool> temp2;
    
    for(size_t j = i+1; j < (asmToBin.number1Val).size(); j++){
        temp1.push_back((asmToBin.number1Val).at(j));
        temp2.push_back((asmToBin.isConstantNumber1).at(j));
    }
    
    asmToBin.number1Val = temp1;
    asmToBin.isConstantNumber1 = temp2;
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    
    cout << "value in FP: " << Ri << endl;
}

// Needs to be fixed
void LOAD(string &Ri, string Rj, AsmBinary &asmToBin, DataMemory & memory, Clock &clockTime){   // Loading memory Rj into Ri
    cout << endl << "------LOAD------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
        
    if(asmToBin.aluOp == 1){

        Number val((memory.memVal).front());
        val.CONVERT_TO_FLOATING_POINT();  
        Ri = val.GET_NUMBER(); // Load Rj value into Ri
            
        reverse((memory.memVal).begin(), (memory.memVal).end());
        (memory.memVal).pop_back();
        reverse((memory.memVal).begin(), (memory.memVal).end());
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    
    cout << "Ri: " << Ri << endl;
    
}

// Needs to be fixed
void STORE(string Ri, string &Rj, AsmBinary &asmToBin, DataMemory &memory, Clock &clockTime){  // Store memory Ri into Rj
    cout << endl << "------STORE------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Ri = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    // Storing the value of Ri into the memory Rj if the control signals have been met.
    if(asmToBin.aluOp == 1){
        // (memory.memVal).push_back(Ri);  // Store Ri value into Rj memory location
        // (asmToBin.location).at(pos2) = (asmToBin.location).at(pos1);  // Store the memory location into Ri into Rj
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    
    cout << "Output of STORE (Rj): " << Rj << endl;
    cout << "Output of STORE (Ri): " << Ri << endl;
}


void MOVE(string &Ri, string &Rj, AsmBinary &asmToBin, Clock &clockTime){  // Moving Rj into Ri
    cout << endl << "------MOVE------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    
    cout << "Input  of MOVE (Ri): " << Ri << endl;  
    cout << "Input  of MOVE (Rj): " << Rj << endl;
    
    // Moving the value of Rj into Ri if the control signals are met.
    if(asmToBin.aluOp == 1){
        Ri = Rj;  // Store Rj value into Ri
        Rj = "";
        
        // Passing the result into the variable that holds the forward value
        if(asmToBin.forwardA == 1){
            asmToBin.forwardValueA = Ri;
            asmToBin.forwardA = 0;
        }
        if(asmToBin.forwardB == 1){
            asmToBin.forwardValueB = Ri;
            asmToBin.forwardB = 0;
        }

    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    
    cout << "Output of MOVE (Ri): " << Ri << endl;
}

void ADD(string &Ri, string Rj, string Rk, AsmBinary & asmToBin, Clock &clockTime){
    if(asmToBin.calledAdd != 1)
        cout << endl << "------ADD------" << endl;
        
    if(asmToBin.calledAdd != 1){
        // Retrieving the forwarded value
        if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
            cout << "Values were forwarded to this ADD" << endl;
            Rj = asmToBin.forwardValueA;
            asmToBin.forwardRjExecute = 0;
            asmToBin.forwardRjMem = 0; 
            asmToBin.forwardRjWrite = 0;
        }
            
        if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
            Rk = asmToBin.forwardValueB;
            asmToBin.forwardRkExecute = 0;
            asmToBin.forwardRkMem = 0; 
            asmToBin.forwardRkWrite = 0;
        }
    }
    
    if(asmToBin.calledAdd != 1){
        cout << "Input  of ADD (Rj): " << Rj << endl;
        cout << "Input  of ADD (Rk): " << Rk << endl;
    }

    if((asmToBin.aluOp == 1 && asmToBin.aluSrc == 0) || asmToBin.calledAdd == 1){
        // Accounting for the one of the numbers being zero
        if(Rj == "00000000000000000000000000000000"){
            Ri = Rk;
        }else if(Rk == "00000000000000000000000000000000"){
            Ri = Rj;
        }else{
            // Creating instances of Number to convert the registers values to decimal
            // 32 Floating Point Strings
            Number number2(Rj);
            Number number3(Rk);
            
            // Splitting Floating Points into S, E, M
            string sign_number2 = (number2.GET_NUMBER()).substr(0,1);
            string exponent_number2 = (number2.GET_NUMBER()).substr(1,8);
            string exponent_number2_temp = exponent_number2;
            string mantissa_number2 = (number2.GET_NUMBER()).substr(9,32);
        
            string sign_number3 = (number3.GET_NUMBER()).substr(0,1);
            string exponent_number3 = (number3.GET_NUMBER()).substr(1,8);
            string exponent_number3_temp = exponent_number3;
            string mantissa_number3 = (number3.GET_NUMBER()).substr(9,32);
        
            string sign_result = "0";
            string exponent_result = "00000000";
            string mantissa_result = "00000000000000000000000";
        
            // Converting the registers values (Floating Point) to decimal
            int R1_exponent = number2.CONVERT_TYPE(exponent_number2_temp);
            int R2_exponent = number3.CONVERT_TYPE(exponent_number3_temp);
            R1_exponent = number2.BINARY_TO_DECIMAL_EXPONENT(R1_exponent);
            R2_exponent = number3.BINARY_TO_DECIMAL_EXPONENT(R2_exponent);
            
            string R1 = number2.CONVERT_TO_DECIMAL();
            string R2 = number3.CONVERT_TO_DECIMAL();
            
            // Converting the numbers from string to doubles
            double numR1 = number2.CONVERT_TYPE(R1); // Base 10 Number
            double numR2 = number2.CONVERT_TYPE(R2); // Base 10 Number
        
            // Special cases where you may be adding negative numbers. Call subtract.
            if(sign_number2 == "0" && sign_number3 == "1" && asmToBin.calledAdd == 0){
                // For Rj - Rk, Both need to be positive so I am negating Rk
                asmToBin.calledSub = 1;
                NEGATE(Rk, Rk, asmToBin, clockTime);
                
                SUBTRACT(Ri, Rj, Rk, asmToBin, clockTime);
            }else if(sign_number2 == "1" && sign_number3 == "0" && asmToBin.calledAdd == 0){
                // Switch Rj and Rk so that We can Perform Rk - Rj and Negate because subtract already accounts for the negative
                asmToBin.calledSub = 1;

                NEGATE(Rj, Rj, asmToBin, clockTime);
                SUBTRACT(Ri, Rk, Rj, asmToBin, clockTime);
            }
            else{
                if (numR1 > numR2) {
                    if(numR1 < 0) {    // Is R1 Negative?
                        sign_result = "1";
                    }
                    else if(numR2 < 0){ // Is R2 Negative?
                        double R2_ABS = numR2 * -1;
                        if(R2_ABS > numR1){    // Is the magnitude of R2 greater than R1?
                            sign_result = "1";
                        }
                    }
                    else{
                        sign_result = "0";
                    }
                }
                
                else if(numR2 > numR1) {
                    if(numR2 < 0) {    // Is R2 Negative?
                        sign_result = "1";
                    }
                    else if(numR1 < 0){ // Is R1 Negative?
                        double R1_ABS = numR1 * -1;
                        if(R1_ABS > numR2){    // Is the magnitude of R1 greater than R2?
                            sign_result = "1";
                        }
                    }
                    else{
                        sign_result = "0";
                    }
                }
                else{
                    sign_result = sign_number2;
                }
        
               // Check for resulting exponent (Step 1)
                // int exponent_difference = abs(R1_exponent - R2_exponent);
                string shifter;
                string hiddenBit;
                if(R1_exponent > R2_exponent){
                    exponent_result = exponent_number2;
                    // Check for hidden bit
                    // if((R2_exponent - 127) >= 0)
                        hiddenBit = "1";
                    // else 
                        // hiddenBit = "0";
                } 
                else if (R1_exponent == R2_exponent){
                    exponent_result = exponent_number2;
                }
                else if(R1_exponent < R2_exponent) {
                    exponent_result = exponent_number3;
                    // Check for hidden bit
                    // if((R1_exponent - 127) >= 0)
                        hiddenBit = "1";
                    // else 
                        // hiddenBit = "0";
                }
                
                
                // Check for resulting mantissa
                int exponent_difference = abs(R1_exponent - R2_exponent);
                for(int i = 0; i < exponent_difference; i++){ // "Shift the number with the smaller exponent by "exponent_difference" spaces to the right (insert 0’s for any spaces above 1 right shift)""
                    if (i == 0){
                        shifter = hiddenBit + shifter;
                    }
                    else{
                        shifter = "0" + shifter;
                    }
                }

                if (R1_exponent > R2_exponent){
                    mantissa_number3 = "0." + shifter + mantissa_number3;      // Add shifter
                    mantissa_number2 = "1." + mantissa_number2;
                    mantissa_number3 = mantissa_number3.substr(0,25);   // Delete excess
                }
                else if (R1_exponent == R2_exponent){
                    mantissa_number2 = "1." + mantissa_number2;      
                    mantissa_number3 = "1." + mantissa_number3;
                    
                    if(mantissa_number3.size() > 25)
                        mantissa_number2 = mantissa_number2.substr(0,25);   // Delete excess
                }
                else{
                    mantissa_number2 = "0." + shifter + mantissa_number2;      // Add shifter
                    mantissa_number3 = "1." + mantissa_number3;
                    mantissa_number2 = mantissa_number2.substr(0,25);   // Delete excess
                }
                
                // Adding the mantissas
                    mantissa_result = number2.ADD_MANTISSA(mantissa_number2, mantissa_number3);
                
                // Nomalizing the exponent
                size_t posPeriod1; // Position of the period
                size_t posPeriod2; // Position of the first 1 in the mantissa;
                
                for(size_t i = 0; i < mantissa_result.size(); i++){
                    if(mantissa_result.at(i) == '.')
                        posPeriod1 = i;
                }
                
                posPeriod2 = mantissa_result.find_first_of('1');
                
                // When the decimal is the first digit then shift to the right
                if(mantissa_result.front() == '.'){
                    mantissa_result.insert(posPeriod2 + 1, ".");
                    
                    posPeriod1 = mantissa_result.find_first_of("1");
                    
                    mantissa_result = mantissa_result.substr(posPeriod1, mantissa_result.size());
                    
                    // Make the mantissa 23 bits again.
                    for(size_t i = mantissa_result.size(); i < 23; i++){
                        mantissa_result.push_back('0');
                    }
                    
                    // Normalizing the exponent by adding the amount shifted to normalize the mantissa
                    string exponentNomalize = number2.CONVERT_TYPE(posPeriod2);
                    exponentNomalize = number2.CONVERT_TO_BINARY(exponentNomalize);
                    
                    exponent_result = number2.SUB_BIT_STRINGS(exponent_result, exponentNomalize);
        
                    
                } else if(mantissa_result.at(1) == '.'){
                    // When the result does not need to be normailzed
                    mantissa_result = mantissa_result.substr(posPeriod1 + 1, mantissa_result.size());
                    
                }else{
                    // When the decimal is not the first digit then shift to the left
                    mantissa_result.erase(posPeriod1, 1);
                    mantissa_result.insert(posPeriod2 + 1, ".");
                    
                    posPeriod2 = mantissa_result.find_first_of(".");
                    
                    mantissa_result = mantissa_result.substr(posPeriod2 + 1, 23);
                     
                    // Normalizing the exponent by adding the amount shifted to normalize the mantissa
                    posPeriod2 = posPeriod1 - posPeriod2;
                    string exponentNomalize = number2.CONVERT_TYPE(posPeriod2);
                    
                    exponentNomalize = number2.CONVERT_TO_BINARY(exponentNomalize);
                    
                    exponent_result = number2.ADD_BIT_STRINGS(exponent_result, exponentNomalize);
                }
        
                string result = sign_result + exponent_result + mantissa_result; //+ mantissa_GRS_result
            
                // Setting the value of Ri to the addition of Rj and Rk
                Ri = result;
            }
        }
    }
    
    // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1 && asmToBin.calledAdd != 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1 && asmToBin.calledAdd != 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
        }
    
    // Used to suppress the output of the negate, add, or subtract if the functions are being called from another function
    if(asmToBin.calledAdd == 1){
        asmToBin.calledAdd = 0;
    }
    else{
        // Adding the alu clock cycles to the clock cycles in main.cpp
        // Updating the cycle count. Cycles hold the number of cycles that have been ran
        clockTime.cycles += 3;
        clockTime.ACTIVATE_CLOCK(.003); // Activating the clock each cycle
        
        // Outputting Ri
        Number number;
        cout << "Output of ADD: " << Ri << endl;
        number.SET_NUMBER(Ri);
        number.CONVERT_TO_DECIMAL();
        cout << "Output of ADD: " << number.GET_NUMBER() << endl;
        }
}

void SUBTRACT(string &Ri, string Rj, string Rk, AsmBinary &asmToBin, Clock &clockTime){
    if(asmToBin.calledSub == 0)
        cout << endl << "------SUBTRACT------" << endl;
        
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
        Rk = asmToBin.forwardValueB;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRkMem = 0; 
        asmToBin.forwardRkWrite = 0;
    }
        
    if(asmToBin.calledSub == 0){
        cout << "Input  of SUBTRACT (Rj): " << Rj<< endl;
        cout << "Input  of SUBTRACT (Rk): " << Rk << endl << endl;
    }
    
    
    // Creating instances of Number to convert the registers values to decimal
    Number number2(Rj);
    Number number3(Rk);

    // Converting the registers values to decimal
    number2.CONVERT_TO_DECIMAL();
    number3.CONVERT_TO_DECIMAL();

    // Converting the numbers from string to double
    double R1= number2.CONVERT_TYPE(number2.GET_NUMBER());
    double R2 = number2.CONVERT_TYPE(number3.GET_NUMBER());

     // Adding the numbers and converting back to string
    Ri = number2.CONVERT_TYPE(R1 - R2);

     // Converting back to floating point
    Number number4(Ri);

    number2.CONVERT_TO_FLOATING_POINT();
    number3.CONVERT_TO_FLOATING_POINT();
    number4.CONVERT_TO_FLOATING_POINT();
    Ri = number4.GET_NUMBER();
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1 && asmToBin.calledSub == 0){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1 && asmToBin.calledSub == 0){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }


    // Output
    if(asmToBin.calledSub == 0){ 
        // Adding the alu clock cycles to the clock cycles in main.cpp
        // Updating the cycle count. Cycles hold the number of cycles that have been ran
        clockTime.cycles += 3;
        clockTime.ACTIVATE_CLOCK(.003); // Activating the clock each cycle
        
        Number number;
        cout << "Output of SUBTRACT: " << Ri << endl;
        number.SET_NUMBER(Ri);
        number.CONVERT_TO_DECIMAL();
        cout << "Output of SUBTRACT: " << number.GET_NUMBER() << endl;
    }
    else{
        asmToBin.calledSub = 0;
    }
}

void NEGATE(string &Ri, string &Rj, AsmBinary &asmToBin, Clock &clockTime){
    if(asmToBin.calledAdd != 1 && asmToBin.calledSub != 1)
        cout << endl << "------NEGATE------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    
    string temp = Rj;
    
    // Negating the sign bit if the aluOp is a 1
    if(asmToBin.aluOp == 1){
        if(Rj.front() == '1'){
            temp.front() = '0';
        }else{
            temp.front() = '1';
        }
    }
    
    // Writing back to the register Ri if regWrite is a 1 and memToReg is 0
    Ri = temp;
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1 && asmToBin.calledAdd != 1 && asmToBin.calledSub != 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1 && asmToBin.calledAdd != 1 && asmToBin.calledSub != 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

        
    if(asmToBin.calledAdd != 1 && asmToBin.calledSub != 1){
        cout << "Input  of NEGATE (Rj): " << Rj << endl;
        cout << "Output of NEGATE (Ri): " << Ri << endl;   
        
        // Adding the alu clock cycles to the clock cycles in main.cpp
        // Updating the cycle count. Cycles hold the number of cycles that have been ran
        (clockTime.cycles)++;
        clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    }
}
    
void MULTIPLY(string &Ri, string Rj, string Rk, AsmBinary& asmToBin, Clock &clockTime){
    cout << endl << "------MULTIPLY------" << endl;
    

    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
        Rk = asmToBin.forwardValueB;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRkMem = 0; 
        asmToBin.forwardRkWrite = 0;
    }
     
    // Creating instances of Number to convert the registers values to decimal.
    // Passing in Rj into the ALU
    Number number2(Rj);
    
    Number number3;
    // Passing in Rk into the ALU if the aluSrc is 0
    if(asmToBin.aluSrc == 0){
        number3.SET_NUMBER(Rk);
    }

    cout << "Input  of MULTIPLY (Rj): " << Rj << endl;
    cout << "Input  of MULTIPLY (Rk): " << Rk << endl;
    // Converting the registers values to decimal.
    number2.CONVERT_TO_DECIMAL();
    number3.CONVERT_TO_DECIMAL();
    
    // Converting the numbers from string to double.
    double R1 = number2.CONVERT_TYPE(number2.GET_NUMBER());
    double R2 = number2.CONVERT_TYPE(number3.GET_NUMBER());

    // Outputting Rj and Rk
    //cout << "Output of MULTIPLY (Rj): " << R1 << endl;
    //cout << "Output of MULTIPLY (Rk): " << R2 << endl;
    
    // Multiplying the numbers and converting back to string.
    if(asmToBin.aluOp == 1)
        Ri = number2.CONVERT_TYPE(R1 * R2);

    // Converting back to floating point.
    Number number4(Ri);
    number2.CONVERT_TO_FLOATING_POINT();
    number3.CONVERT_TO_FLOATING_POINT();
    number4.CONVERT_TO_FLOATING_POINT();
    
    // Ri = Rj*Rk
    Ri = number4.GET_NUMBER();
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    if(Rj == "00111111100000000000000000000000" || Rk == "00111111100000000000000000000000" || Rj == "10111111100000000000000000000000" || Rk == "10111111100000000000000000000000" || Rj == "00000000000000000000000000000000" || Rk == "00000000000000000000000000000000"){
        clockTime.cycles += 1;
        clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
    }else{
        clockTime.cycles += 8;
        clockTime.ACTIVATE_CLOCK(.008); // Activating the clock each cycle
    }
    
    // Outputting Ri
    Number number;
    cout << "Output of MULTIPLY: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of MULTIPLY: " << number.GET_NUMBER() << endl;
}

void DIVIDE(string &Ri, string Rj, string Rk, AsmBinary& asmToBin, Clock &clockTime){
    cout << endl << "------DIVIDE------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
        Rk = asmToBin.forwardValueB;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRkMem = 0; 
        asmToBin.forwardRkWrite = 0;
    }
        
    // Creating instances of Number to convert the registers values to decimal.
    // Passing in Rj into the ALU
    Number number2(Rj);
    
    //cout << endl << "Ri: " << Ri << endl;
    cout << "Input  of DIVIDE (Rj): " << Rj << endl;
    cout << "Input  of DIVIDE (Rk): " << Rk << endl;
    
    Number number3;
    // Passing in Rk into the ALU if the aluSrc is 0
    if(asmToBin.aluSrc == 0)
        number3.SET_NUMBER(Rk);

    // Converting the registers values to decimal.
    number2.CONVERT_TO_DECIMAL();
    number3.CONVERT_TO_DECIMAL();

    // Converting the numbers from string to double.
    double R1 = number2.CONVERT_TYPE(number2.GET_NUMBER());
    double R2 = number2.CONVERT_TYPE(number3.GET_NUMBER());
    
    // Outputting Rj and Rk
    //cout << "Input of DIVIDE: " << R1 << endl;
    //cout << "Input of DIVIDE: " << R2 << endl;

    if(asmToBin.aluOp == 1){
        // Checking for divide by zero.
        try {
            // Set R1 to the division of R1 and R2.
            Ri = number2.CONVERT_TYPE(R1 / R2);
    
            if (R2 == 0) {
                throw 11;
            }
        }
        catch (int x) {
            cout << "Error, trying to divide by zero" << endl;
            exit(1);
        }
    }

    // Converting back to floating point.
    Number number4(Ri);
    number2.CONVERT_TO_FLOATING_POINT();
    number3.CONVERT_TO_FLOATING_POINT();
    number4.CONVERT_TO_FLOATING_POINT();

    // Ri = Rj*Rk
    Ri = number4.GET_NUMBER();
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    clockTime.cycles += 8;
    clockTime.ACTIVATE_CLOCK(.008); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of DIVIDE: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of DIVIDE: " << number.GET_NUMBER() << endl;
}

void FLOOR(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime) {
    if(asmToBin.calledSub == 0)
        cout << endl << "------FLOOR------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    Number convDEC(Rj);

    // Outputting Rj
    if(asmToBin.calledSub == 0)
        cout << "Input  of FLOOR: " << Rj << endl;
    
    Number number2(Rj);
    string result = (number2.GET_NUMBER());
    string signExponent;
    
    if(asmToBin.aluOp == 1){
    
        string inputExponent = (number2.GET_NUMBER()).substr(1, 8);

        // Find Mantissa of the 2nd in the instrution

        // Find n to know where to round
        int n = number2.CONVERT_TYPE(inputExponent);
        n = number2.BINARY_TO_DECIMAL_EXPONENT(n) - 127;
        
        if (n < 0){
            result = "00000000000000000000000000000000";
        }
        else{
            // Bit Level Floor Operation
            // Zero's starting at the nth bit
            for (int i = n + 9; i < 32; i++) {
                result.at(i) = '0';
            }
        }
    } 
    
    // Ri = floor(Rj)
    Ri = result;

     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1 && asmToBin.calledSub != 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    
    if(asmToBin.forwardB == 1 && asmToBin.calledSub != 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Outputting Ri 
    Number number;
        if(asmToBin.calledSub == 0){
        // Adding the alu clock cycles to the clock cycles in main.cpp
        // Updating the cycle count. Cycles hold the number of cycles that have been ran
        clockTime.cycles += 8;
        clockTime.ACTIVATE_CLOCK(.008); // Activating the clock each cycle
    
        cout << "Output of FLOOR: " << Ri << endl;
        number.SET_NUMBER(Ri);
        number.CONVERT_TO_DECIMAL();

        cout << "Output of FLOOR: " << number.GET_NUMBER() << endl;
    }
}

void CEIL(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------CEIL------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    Number convDEC(Rj);

    // OUTPUT (Before)
    cout << "Input  of CEIL: " << Rj << endl;

    Number number2(Rj);
    string result = (number2.GET_NUMBER());
    string inputSign = (number2.GET_NUMBER()).substr(0, 1);
    string inputMantissa = (number2.GET_NUMBER()).substr(9, 23);
    
    if(asmToBin.aluOp == 1){
    
        string inputExponent = (number2.GET_NUMBER()).substr(1, 8);

        // Find Mantissa of the 2nd in the instrution

        //Find n to know where to round
        int n = number2.CONVERT_TYPE(inputExponent);
            
        n = number2.BINARY_TO_DECIMAL_EXPONENT(n) - 127;
        
        asmToBin.calledSub = 1;
        FLOOR(Ri, Rj, asmToBin, clockTime);
        asmToBin.calledSub = 0;
        
        asmToBin.calledAdd = 1;
        ADD(Ri, Ri, "00111111100000000000000000000000", asmToBin, clockTime);
        asmToBin.calledAdd = 0;
    } 
    
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of Ceil: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of Ceil: " << number.GET_NUMBER() << endl;
}

void ROUND(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------ROUND------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    
    Number convDEC(Rj);

    // OUTPUT (Before)
    cout << "Input  of ROUND: " << Rj << endl;

    Number number2(Rj);
    string result = (number2.GET_NUMBER());
    string inputSign = (number2.GET_NUMBER()).substr(0, 1);
    string inputMantissa = (number2.GET_NUMBER()).substr(9, 23);
    bool up = false;
    
    if(asmToBin.aluOp == 1){
    
        string inputExponent = (number2.GET_NUMBER()).substr(1, 8);

        // Find Mantissa of the 2nd in the instrution

        //Find n to know where to round
        int n = number2.CONVERT_TYPE(inputExponent);
            
        n = number2.BINARY_TO_DECIMAL_EXPONENT(n) - 127;
        
        if (result.at(n+9) == '1')
            up = true;
        
        if (n < 0){
            result = "00000000000000000000000000000000";
        }
        else{
            // Bit Level Floor Operation
            // Zero's starting at the nth bit
            for (int i = n + 9; i < 32; i++) {
                result.at(i) = '0';
            }
        }
        
        if (up == true){
            //if (fraction == true){
            asmToBin.calledAdd = 1;
            ADD(Ri, Ri, "00111111100000000000000000000000", asmToBin, clockTime);
            asmToBin.calledAdd = 0;
        }
        else
            Ri = result;
    } 
    
    // Ri = round(Rj)
    //Ri = result;
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of ROUND: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of ROUND: " << number.GET_NUMBER() << endl;
}

void ABS(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------ABSOLUTE VALUE------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    
    Number convDEC(Rj);

    // OUTPUT (Before)
    cout << "Input  of ABS: " << Rj << endl;

    Number number2(Rj);

    string result;
    // Make Value Positive
    if(asmToBin.aluOp == 1)
        result = "0" + (number2.GET_NUMBER()).substr(1, 32);

    // Ri = abs(Rj)
    Ri = result;
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of ABS: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of ABS: " << number.GET_NUMBER() << endl;
}

void MIN(string &Ri, string Rj, string Rk, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------MINIMUM------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
        Rk = asmToBin.forwardValueB;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRkMem = 0; 
        asmToBin.forwardRkWrite = 0;
    }
    // OUTPUT (Before)
    cout << "Input  of MIN (Rj): " << Rj << endl;
    cout << "Input  of MIN (Rk): " << Rk << endl;
    
    // Passing in Rj into the ALU
    Number number2(Rj);
    
    Number number3;
    // Passing in Rk into the ALU if the aluSrc is 0
    if(asmToBin.aluSrc == 0){
        number3.SET_NUMBER(Rk);
    }

    string result;
    if(asmToBin.aluOp == 1){
        // Parce both input numbers
        string number2_binary = number2.GET_NUMBER();
        string number2_sign = (number2.GET_NUMBER()).substr(0, 1);
        string number3_binary = number3.GET_NUMBER();
        string number3_sign = (number3.GET_NUMBER()).substr(0, 1);
    
        // If both inputs are positive
        if (number2_sign == "0" && number3_sign == "0") {
            for (int i = 1; i < 32; i++) {
                if (number2_binary.at(i) != number3_binary.at(i)) {
                    if (number2_binary.at(i) == '1' && number3_binary.at(i) == '0') {
                        result = number3_binary;
                        break;
                    }
                    else {
                        result = number2_binary;
                        break;
                    }
                }
            }
        }
    
        // If 2nd input is negative
        else if (number2_sign == "0" && number3_sign == "1") {
            result = number3_binary;
        }
    
        // If 3rd input is negative
        else if (number2_sign == "1" && number3_sign == "0") {
            result = number2_binary;
        }
    
        // If both inputs are negative
        else {
            for (int i = 1; i < 32; i++) {
                if (number2_binary.at(i) != number3_binary.at(i)) {
                    if (number2_binary.at(i) == '1' && number3_binary.at(i) == '0') {
                        result = number2_binary;
                        break;
                    }
                    else {
                        result = number3_binary;
                        break;
                    }
                }
            }
        }
    }

    // Ri = min(Rj, Rk)
    Ri = result;
    
     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of MIN: " << Ri << endl;
    number.SET_NUMBER(Rj);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of MIN: " << number.GET_NUMBER() << endl;
}

void MAX(string &Ri, string Rj, string Rk, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------MAXIMUM------" << endl;
    
   // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    if(asmToBin.forwardRkExecute == 1 || asmToBin.forwardRkMem == 1 || asmToBin.forwardRkWrite == 1){
        Rk = asmToBin.forwardValueB;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRkMem = 0; 
        asmToBin.forwardRkWrite = 0;
    }

    // OUTPUT (Before)
    cout << "Input  of MAX (Rj): " << Rj << endl;
    cout << "Input  of MAX (Rk): " << Rk << endl;
    
    // Passing in Rj into the ALU
    Number number2(Rj);
    
    Number number3;
    // Passing in Rk into the ALU if the aluSrc is 0
    if(asmToBin.aluSrc == 0){
        number3.SET_NUMBER(Rk);
    }

    string result;
    if(asmToBin.aluOp == 1){
        // Parce both input numbers
        string number2_binary = number2.GET_NUMBER();
        string number2_sign = (number2.GET_NUMBER()).substr(0, 1);
        string number3_binary = number3.GET_NUMBER();
        string number3_sign = (number3.GET_NUMBER()).substr(0, 1);
    
        // If both inputs are positive
        if (number2_sign == "0" && number3_sign == "0") {
            for (int i = 1; i < 32; i++) {
                if (number2_binary.at(i) != number3_binary.at(i)) {
                    if (number2_binary.at(i) == '1' && number3_binary.at(i) == '0') {
                        result = number2_binary;
                        break;
                    }
                    else {
                        result = number3_binary;
                        break;
                    }
                }
            }
        }
    
        // If 3rd input is negative
        else if (number2_sign == "0" && number3_sign == "1") {
            result = number2_binary;
        }
    
        // If 2nd input is negative
        else if (number2_sign == "1" && number3_sign == "0") {
            result = number3_binary;
        }
    
        // If both inputs are negative
        else {
            for (int i = 1; i < 32; i++) {
                if (number2_binary.at(i) != number3_binary.at(i)) {
                    if (number2_binary.at(i) == '1' && number3_binary.at(i) == '0') {
                        result = number3_binary;
                        break;
                    }
                    else {
                        result = number2_binary;
                        break;
                    }
                }
            }
        }
    }

    // Ri = min(Rj, Rk)
    Ri = result;
    
    // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }

    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    (clockTime.cycles)++;
    clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of MAX: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of MAX: " << number.GET_NUMBER() << endl;
}

void POWER(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime){
    cout << endl << "------POWER------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    // OUTPUT (Before)
    cout << "Input  of POWER: " << Rj << endl;

    // Converts the numbers to Decimal
    Number convDEC(Rj);
    Number number1;
    convDEC.CONVERT_TO_DECIMAL();

    double temp_Rj = convDEC.CONVERT_TYPE(convDEC.GET_NUMBER());

    // Setting the starting point for the for loop that loops through the immediate values (#numbers)
    // If it is not branching then loop as normal. If branching, then set the staring location to the line that you looped to.
    
    int it = 0; // Iterator for accessing the immediate value
    string raiseTo; // The immediate value
    size_t i = 0; // Iterator for the for loop that finds the immediate value
    
    // Accessing an immediate value if the aluSrc signal is a 1
    if(asmToBin.aluSrc == 1){
        // If no branching, then loop as normal. 
        // If branching, then set the staring location to the label(line) looped.
        if(asmToBin.tempBranch1 == true){
            if(asmToBin.iterator < 1){
                i = asmToBin.numberLocation - 1;
                asmToBin.iterator = 1;
            }else
                i = 0;
        }
        // Loops through the immediate values (#numbers) to access the correct value to set.
        for (i; i < (asmToBin.number2Val).size(); i++) {
            if ((asmToBin.isConstantNumber2).at(i) == 1) {
                raiseTo = (asmToBin.number2Val).at(i);
                break;
            }
            else {
            }
        }
    }

    if(asmToBin.aluOp == 1){
        // Converting Rk to a double
        double temp_Rk = convDEC.CONVERT_TYPE(raiseTo);
    
        // Performing the power operation
        double temp = pow(temp_Rj, temp_Rk);
        
        // Converting back to a string
        Ri = convDEC.CONVERT_TYPE(temp);
        // Converting back to floating point
        number1.SET_NUMBER(Ri);
        number1.CONVERT_TO_FLOATING_POINT();
    }
    
    // Ri = pow(Rj, #imm)
    Ri = number1.GET_NUMBER();

     // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    clockTime.cycles += 6;
    clockTime.ACTIVATE_CLOCK(.006); // Activating the clock each cycle


    // Outputting Ri
    Number number;
    cout << "Output of POWER: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of POWER: " << number.GET_NUMBER() << endl;

    // Removes the immediate value from the temperary variable once it is set in a register
    vector<string> temp1;
    vector<bool> temp2;

    for (size_t j = i + 1; j < (asmToBin.number2Val).size(); j++) {
        temp1.push_back((asmToBin.number2Val).at(j));
        temp2.push_back((asmToBin.isConstantNumber2).at(j));
    }

    asmToBin.number2Val = temp1;
    asmToBin.isConstantNumber2 = temp2;
}

void EXPONENT(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime) {
    cout << endl << "------EXPONENT------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    Number convDEC(Rj);

    // OUTPUT (Before)
    cout << "Input  of EXPONENT: " << Rj << endl;

    Number number1;
    if(asmToBin.aluOp == 1){ 
         // Converts the number to Decimal
        convDEC.CONVERT_TO_DECIMAL();

        // Adds the 32 bit FP number to the register
        Ri = convDEC.GET_NUMBER();
    
        double temp = convDEC.CONVERT_TYPE(Ri);
    
        // Operation
        temp = exp(temp);
    
        Ri = convDEC.CONVERT_TYPE(temp);
    
        // Converting back to floating point
        number1.SET_NUMBER(Ri);
    
        number1.CONVERT_TO_FLOATING_POINT();
    }

    // Ri = e^Rj
    Ri = number1.GET_NUMBER();
    
    // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardValueB = Ri;
        asmToBin.forwardB = 0;
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    clockTime.cycles += 8;
    clockTime.ACTIVATE_CLOCK(.008); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of EXPONENT: " << Ri << endl;
    number.SET_NUMBER(Rj);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of EXPONENT: " << number.GET_NUMBER() << endl;
}

void SQUARE_ROOT(string &Ri, string Rj, AsmBinary& asmToBin, Clock &clockTime){
    cout << endl << "------SQUARE ROOT------" << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Rj = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }

    // OUTPUT (Before)
    cout << "Input  of SQUARE_ROOT: " << Rj << endl;

    Number number1;
    if(asmToBin.aluOp == 1){
        // Converts the number to Decimal
        Number convDEC(Rj);
        convDEC.CONVERT_TO_DECIMAL();
    
        // Adds the 32 bit FP number to the register
        Ri = convDEC.GET_NUMBER();
    
        // Performing the square root operation
        double temp = convDEC.CONVERT_TYPE(Ri);
    
        // Operation
        temp = sqrt(temp);
    
        // Converting the result to a string
        Ri = convDEC.CONVERT_TYPE(temp);
    
        // Converting back to floating point
        number1.SET_NUMBER(Ri);
        number1.CONVERT_TO_FLOATING_POINT();
    }

    // Ri = √Rj
    Ri = number1.GET_NUMBER();
    
    // Passing the result into the variable that holds the forward value
    if(asmToBin.forwardA == 1){
        asmToBin.forwardValueA = Ri;
        asmToBin.forwardA = 0;
    }
    if(asmToBin.forwardB == 1){
        asmToBin.forwardB = 0;
        asmToBin.forwardValueB = Ri;
    }
    
    // Adding the alu clock cycles to the clock cycles in main.cpp
    // Updating the cycle count. Cycles hold the number of cycles that have been ran
    clockTime.cycles += 8;
    clockTime.ACTIVATE_CLOCK(.008); // Activating the clock each cycle

    // Outputting Ri
    Number number;
    cout << "Output of SQUARE_ROOT: " << Ri << endl;
    number.SET_NUMBER(Ri);
    number.CONVERT_TO_DECIMAL();
    cout << "Output of SQUARE_ROOT: " << number.GET_NUMBER() << endl;
}

void BRANCH_NEGATIVE(string Ri, AsmBinary& asmToBin, Clock &clockTime){ 
    // cout << endl << "------BRANCH NEGATIVE------" << endl << endl;
   
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Ri = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRkExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
        
    }

//     asmToBin.iterator = 0; // Resetting the iterator that determines what postion to start accessing the #numbers
    
//     // Converting the branch label(line) to an int
//     Number convert;
//     int branchLabel = convert.CONVERT_TYPE((asmToBin.branchVal1).front()); // Temp variable that holds the line to branch to

//     // If the value of the register is negative, then set the label(line) into branching location
//     if (Ri.front() == '1'){
//         asmToBin.branchingLocation = branchLabel; // Holds the line to branch to

//         // Setting the branch boolean
//         asmToBin.branch = 1;
//     }else{
//         // Setting the branch boolean
//         asmToBin.branch = 0;
//     }
    
//     // Adding the alu clock cycles to the clock cycles in main.cpp
//     // Updating the cycle count. Cycles hold the number of cycles that have been ran
//     clockTime.cycles += 3;
//     clockTime.ACTIVATE_CLOCK(.003); // Activating the clock each cycle
    
//     if(asmToBin.branch == 1)
//         cout << "Branch Taken" << endl;
//     else
//         cout << "Branch Not Taken" << endl;

//     // Removing the first element in branchingVal1, So next time the function gets called it will have the correct line number to branch to
//     if(asmToBin.branch == 1)
//         (asmToBin.branchVal1).erase(((asmToBin.branchVal1).begin()));
}

void BRANCH_ZERO(string Ri, AsmBinary& asmToBin, Clock &clockTime) {
    // cout << endl << "------BRANCH ZERO------" << endl << endl;
    
    // Retrieving the forwarded value
    if(asmToBin.forwardRjExecute == 1 || asmToBin.forwardRjMem == 1 || asmToBin.forwardRjWrite == 1){
        Ri = asmToBin.forwardValueA;
        asmToBin.forwardRjExecute = 0;
        asmToBin.forwardRjMem = 0; 
        asmToBin.forwardRjWrite = 0;
    }
    
    // // Converting the branch label(line) to an int
    // Number convert;

    // asmToBin.iterator = 0; // Resetting the iterator that determines what postion to start accessing the #numbers

    // int branchLabel = convert.CONVERT_TYPE((asmToBin.branchVal1).front()); // Temp variable that holds the line to branch to

    // // If the value of the register is negative, then set the label(line) into branching location
    // if (Ri == "00000000000000000000000000000000") {
    //     asmToBin.branchingLocation = branchLabel; // Holds the line to branch to

    //     //Setting the branch boolean
    //     asmToBin.branch = 1;
    // }else{
    //     //Setting the branch boolean
    //     asmToBin.branch = 0;
    // }
    
    // // Adding the alu clock cycles to the clock cycles in main.cpp
    // // Updating the cycle count. Cycles hold the number of cycles that have been ran
    // clockTime.cycles += 3 ;
    // clockTime.ACTIVATE_CLOCK(.003); // Activating the clock each cycle
    
    // if(asmToBin.branch == 1)
    //     cout << "Branch Taken" << endl;
    // else
    //     cout << "Branch Not Taken" << endl;

    // // Removing the first element in branchingVal1, So next time the function gets called it will have the correct line number to branch to
    // if(asmToBin.branch == 1)
    //     (asmToBin.branchVal1).erase(((asmToBin.branchVal1).begin()));
}

void BRANCH(AsmBinary& asmToBin, Clock &clockTime) {
    // cout << endl << "------BRANCH UNCONDITIONALLY------" << endl << endl;

    // // Converting the branch label(line) to an int
    // Number convert;

    // asmToBin.iterator = 0; // Resetting the iterator that determines what postion to start accessing the #numbers

    // int branchLabel = convert.CONVERT_TYPE((asmToBin.branchVal2).front()); // Temp variable that holds the line to branch to
    
    // // Adding the alu clock cycles to the clock cycles in main.cpp
    // // Updating the cycle count. Cycles hold the number of cycles that have been ran
    // (clockTime.cycles)++ ;
    // clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle

    // // If the value of the register is negative, then set the label(line) into branching location
    // asmToBin.branchingLocation = branchLabel; // Holds the line to branch to

    // // Removing the first element in branchingVal2, So next time the function gets called it will have the correct line number to branch to
    //     (asmToBin.branchVal2).erase(((asmToBin.branchVal2).begin()));
}

void NO_OPERATION(Clock &clockTime) {
    cout << endl << "------NO-OP EXECUTED------" << endl << endl;
    
    clockTime.ACTIVATE_CLOCK(.001); // Calling the clock at 100ns
}

void HALT(){
    cout << endl << "------HALT------" << endl << endl;
    exit(1);
}