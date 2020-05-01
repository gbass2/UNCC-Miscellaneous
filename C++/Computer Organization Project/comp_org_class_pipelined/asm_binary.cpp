#include "asm_binary.h"
#include "number.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <iostream>

// Defines the sleep function. Uses Windows.h if the operating system is Windows and uses unistd.h if using Linux
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Functions for converting from ASM to binary for the registers 
string RegisterFile::FINDING_REGISTER_FROM_BINARY(string registerInASM){
  
    // Creating a map to hold the the register in ASM and return the binary represintation of the register
    map <string, string> registerMap;
  
    // Adding the ASM and binary register representation to map
    for(size_t i = 0; i < this->registerInASM.size(); i++){
        registerMap.insert(make_pair(this->registerInASM[i], this->registerInBinary[i]));
    }
     for(size_t i = 0; i < this->tempRegAsm.size(); i++){
        registerMap.insert(make_pair(this->tempRegAsm[i], this->tempRegBin[i]));
    }
    // Change from ASM to binary
    string registerBin = registerMap.find(registerInASM)->second;
  
    return registerBin;
}
  
    // Function for converting from binary to ASM for the registers
string RegisterFile::FINDING_REGISTER_ASM_FROM_BINARY(string registerBin){
    
    // Creating a map to hold the the register in binary and return the ASM represintation of the register
    map <string, string> registerMap;
  
    // Adding the binary and ASM register representation to map
    for(size_t i = 0; i < this->registerInBinary.size(); i++){
        registerMap.insert(make_pair(this->registerInBinary[i], this->registerInASM[i]));
    }
    for(size_t i = 0; i < this->tempRegAsm.size(); i++){
        registerMap.insert(make_pair(this->tempRegBin[i], this->tempRegAsm[i]));
    }
    // Change from ASM to binary
    string registerInASM = registerMap.find(registerBin)->second;
  
    return registerInASM;
}

string Opcode::FINDING_OPCODE_BINARY_FROM_ASM(string opcodeInASM){
    // Creating a map to hold the the register in ASM and return the binary represintation of the register
    map <string, string> registerMap;
  
    // Adding the ASM and binary register representation to map
    for(size_t i = 0; i < this->opcodeInASM.size(); i++){
        registerMap.insert(make_pair(this->opcodeInASM[i], this->opcodeInBinary[i]));
    }
    // Change from ASM to binary
    string opcodeBin = registerMap.find(opcodeInASM)->second;
    return opcodeBin;
}

string Opcode::FINDING_OPCODE_ASM_FROM_BINARY(string opcodeBin){
    // Creating a map to hold the the register in ASM and return the binary represintation of the register
    map <string, string> registerMap;
  
    // Adding the ASM and binary register representation to map
    for(size_t i = 0; i < this->opcodeInBinary.size(); i++){
        registerMap.insert(make_pair(this->opcodeInBinary[i], this->opcodeInASM[i]));
    }
    
    // Change from ASM to binary
    string opcodeInASM = registerMap.find(opcodeBin)->second;
  
    return opcodeInASM;
}

// Converts the set of instructions to 32 bit binary strings
string AsmBinary::CONVERT_ASM_TO_BINARY(){
    if(!R1.empty() || !R2.empty() || !R3.empty()){
        // If R1 contain just whitespace, it is cleared
        bool whiteSpacesOnly1 = R1.find_first_not_of (' ') == R1.npos;
            if(whiteSpacesOnly1){
                R1 = "";
            }
        
        // Determining if the number coming in is a braching label(line). If so, then push back to branchVal
        if(R1.front() != '#' && R1.front() != 'R' && !R1.empty())
            branchVal2.push_back(R1);
        
        string R4 = R2;
        
        // If R2 contain just whitespace, it is cleared
        bool whiteSpacesOnly2 = R2.find_first_not_of (' ') == R2.npos;
            if(whiteSpacesOnly2){
                R2 = "";
            }
            
            // Determining if the number coming in has a '#' or not. If so, then push back false, If not, then push back false;
            if(R2.front() != '#' && !R2.empty())
                isNumber2.push_back(true);
            else 
                isNumber2.push_back(false);
                
            // Determining if the number coming in is a braching label(line). If so, then push back to branchVal
            if(R2.front() != '#' && R2.front() != 'R' && !R2.empty())
                branchVal1.push_back(R2);
            
            // Determining if the number coming in has a '#' or not. If so, then push back true, If not, then push back false;    
            if(R2.front() == '#' && !R2.empty()){
                R2.erase(0,1);
                number1Val.push_back(R2);
                isConstantNumber1.push_back(1);
            }else if(R2.front() != '#' && !R2.empty()){
                number1Val.push_back("0");
                isConstantNumber1.push_back(0);
            }
            
             // If R3 contain just whitespace, it is cleared
            bool whiteSpacesOnly3  = R3.find_first_not_of (' ') == R3.npos;
            if(whiteSpacesOnly3){
                R3 = "";
            }
            
            // Determining if the number coming in has a '#' or not. If so, then push back false, If not, then push back false;
            if(R3.front() != '#' && !R3.empty())
                isNumber3.push_back(true);
            else 
                isNumber3.push_back(false);
            
            // Determining if the number coming in has a '#' or not. If so, then push back true, If not, then push back false;    
            if(R3.front() == '#' && !R3.empty()){
                R3.erase(0,1);
                number2Val.push_back(R3);
                isConstantNumber2.push_back(1);
            }else{
                isConstantNumber2.push_back(0);
                number2Val.push_back("0");
            }
        
        // Used for outputting the ASM for milestone 1
        if(R2.front() == '#' || (R2.front() != 'R' && R2.front() != '#')){
            
            // Loops through tempValue and if an element is empty, the number is stored in it and R2 is set to the value of the temperary register
            for(size_t i = 0; i < tempValue.size(); i++){
                if(tempValue[i] == "0" && !R2.empty()){
                    tempValue[i] = R2;
                    R2 = tempRegAsm.at(i);
                    break;
                }
            }
            
        // Used for outputting the ASM for milestone 1  
        }else if(R3.front() == '#'|| (R3.front() != 'R' && R3.front() != '#')){
            
            // Loops through tempValue and if an element is empty, the number is stored in it and R3 is set to the value of the temperary register
            for(size_t i = 0; i < tempValue.size(); i++){
                if(tempValue.at(i) == "0" && !R3.empty()) {
                    tempValue.at(i) = R3;
                    R3 = tempRegAsm.at(i);
                    break;
                }
            }
        }
    }
    
    // Converting the opcode, R1, and R2 to binary
    op = FINDING_OPCODE_BINARY_FROM_ASM(op);
    R1 = FINDING_REGISTER_FROM_BINARY(R1);
    R2 = FINDING_REGISTER_FROM_BINARY(R2);
    
    // Determining if R3 is epmty, if it is empty then the register is filled with zeros. If not, then the register is converted to binary
    if(R1.empty()){
        R1 = "00000000";
        isZero1 = 1;
    }
    if(R2.empty()){
        R2 = "00000000";
        isZero2 = 1;
    }
    
    if(R3.empty()){
        R3 = "00000000";
        isZero3 = 1;
    } else {
        R3 = FINDING_REGISTER_FROM_BINARY(R3);  
    }
    
    // Storing the value of the binary string for later use. Need to make it a vector if to use later
    return storedValueBinary = op + R1 + R2+ R3;
}

// Milestone 1
//converting Binary output back to ASM
string AsmBinary::CONVERT_BINARY_TO_ASM(string binary, int &j, int &k){
    //Split 32 bit input
    string opcodeBin = binary.substr(0,8); // opcodeInBinary
    string Rm = binary.substr(8,8);  // Rm 
    string Rn = binary.substr(16,8); // Rn
    string Rd = binary.substr(24,8); // Rd
    
    // If any of the registers have an all zeors, the register is ignored
    if (Rd == "00000000"){
        Rd = "";
    }
    if (Rm == "00000000"){
        Rm = "";
    }
    if (Rn == "00000000"){
        Rn = "";
    }
    
    // Converting the binary string into ASM
    string op = FINDING_OPCODE_ASM_FROM_BINARY(opcodeBin); 
    Rm = FINDING_REGISTER_ASM_FROM_BINARY(Rm);
    Rn = FINDING_REGISTER_ASM_FROM_BINARY(Rn);
    Rd = FINDING_REGISTER_ASM_FROM_BINARY(Rd);
    
    // Looping through tempRegAsm and if the register equals Rm,Rn,Rd the value is taken and added a '#' if needed
    //j is a number we increment
    for(k; k < isNumber1.size() + 1; k++){
        for(size_t i = 0; i < tempRegAsm.size(); i++){
            if(Rn == tempRegAsm.at(i)){
                // If the number at tempValue(j) is not supposed to have a '#' then the '#' is ignored
                if(isNumber2.at(k) == true)
                    Rn = tempValue.at(j);
                else
                    Rn = "#" + tempValue.at(j);
                j++;
            }else if(Rd == tempRegAsm.at(i)){
                // If the number at tempValue(j) is not supposed to have a '#' then the '#' is ignored
                if(isNumber3.at(k) == true)
                    Rd = tempValue.at(j);
                else
                    Rd = "#" + tempValue.at(j);
                j++;
            }
        }
        k++;
        break;
    }
    
    // Storing the value of the ASM string for later use. Need to make it a vector if to use later
    return storedValueASM = op + " " + Rm + " " +  Rn + " " + Rd;
}

void Clock::ACTIVATE_CLOCK(int time){
    
    // Suspends the program for the specified time
    usleep(time);
}


// Returning the value of the register
string RegisterFile::GET_VALUE(string reg, bool resultRegPos){
    int regPos;
    for(size_t i = 0; i < registerInBinary.size(); i++){
        if(registerInBinary.at(i) == reg)
            regPos = i;
    }

    // Setting the pos of the write register into a vector to be accessed when writing
    if(resultRegPos == 1)
        RiPos.push_back(regPos); // Setting the position of Ri into a variable for writing back to the register later

    
    return value.at(regPos);
}

void RegisterFile::WRITE_VALUE(string result){
    int pos = RiPos.front();
    value.at(pos) = result;
    
    // removing the first value of Ri vector to have the correct position to access next time
    reverse(RiPos.begin(), RiPos.end());
    RiPos.pop_back();
    reverse(RiPos.begin(), RiPos.end());
}

void setLocationToValue(string memLocation, string memValue){
    // map<string, string>loc2val;
    
    // for (int i = 0; memVal <= 100; i++){   //Idk how large the map need to be
    //     for (int j = 0; tempLocation <= 100, j++){ // therefore I setted as 100 to be big enough
    //         loc2val[i] = j;
    //     }   
    // }
    // tempLocation = memLocation;
    // memVal = memValue;
}

string getLocationToValue(){
    // return memVal;
}
  
void setValueToLocation(string memLocationm, string memValue){
    // map<string, string>val2loc;
    
    //  for (int i = 0; tempLocation <= 100; i++){   //Idk how large the map need to be
    //     for (int j = 0; memVal <= 100, j++){ // therefore I setted as 100 to be big enough
    //         loc2val[i] = j;
    //     }   
    // }
    // tempLocation = memLocation;
    // memVal = memValue;
    
}

string getValueToLocation(){
    // return tempLocation;    
}
