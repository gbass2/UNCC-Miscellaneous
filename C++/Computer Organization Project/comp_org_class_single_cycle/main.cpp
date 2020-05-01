///-----------------------------------------------------------------
///   Class:          ECGR 3183 Computer Organization 
///   Description:    Simulating how a processor executes instructions
///   Author:         Grayson Bass, Landon Gibson, Sam Xu            
///   Name:           Comp Org Project Pipeline          Date: 4/26/2020 
///
///   Revisions:      Milestone 0: Created functions to convert between floating point and decimal
///                     
///                   Milestone 1: Parsing the input file and reading in the instruction.
///                                Converting between asm and binary
///
///                   Milestone 3: Created the if else statement to execute the instructions
///                                Implemented all functions to execute the instructions some not at bit level
///                                Implemented branching without prediction
///                                Started to add control signals
///
///                   Milestone 4: Cleaned up the code and added more comments
///                                Added a method to class Number that adds two binary strings
///                                Mostly Finished implementing instructions at bit level
///                                Finished the control signals
///                   
///                   Milestone 5: Implemented a clock for the single cycle and pipelined
///                                Implemented Pipelining
///                                Fixed subtraction function
///                                Fixed the way we implement memory
///
///    Files:          asm_binary holds the different functional blocks as well as an extra class for any extra cross file variables and functions
///                    number holds the conversions for floating point as well as type converstions and the addition of the mantissas
///                    instr_functions holds the functions to execute the alu operations as well as the pipeline FDXMW
///
///   References:     Link to the source that helped with reading in from a file
///                   http://www.cplusplus.com/forum/beginner/121749/
///                   Link to the source that helped us add binary numbers
///                   https://www.geeksforgeeks.org/
///-----------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "number.h"
#include "asm_binary.h"
#include "instr_functions.h"

using namespace std;

int main(){
    
    ifstream inFile("textInput.txt"); //open the file set label as "inFile"
    vector<vector<string>>  wordIn; // multi dementional vector to hold the file's content
    
    if(!inFile){ //check the file is opened correctly
        cout << "Unable to open the file: " << endl;
        exit(1);
    }
        
        // These classes can be found in the asm_binary file
        AsmBinary asmToBin; // Creating an instance of AsmBinary. This is used to access the different functional blocks
        InstructionMemory instructionMemory; // An instance of the functional block that holds the instructions
        ProgramCounter programCounter; // An instance of the functional block that holds the Program Counter
        RegisterFile registers; // An instance of the functional block that holds the registers
        DataMemory memory; // An instance of the functional block that holds the memory
        Clock clockTime; // An instance of the clock. Allows for the Activate Clock function to be called
        
        string line; 
        vector<string> tokens; // Holds the contents of the current line being read by the file
        
        // Fetching the instruction
        // Trying to read word by word. If a "--" is found then skip to the next line
        // The line read is added to an nXn vector wordIn to store the contents of the file
    	while (getline(inFile, line)){
    		istringstream ls(line);
    		string token; // The current word read from the file
    		
    		// Loops until the last line of the file
    		while ( ls >> token ){ // Removes comments
    		    if(token == "--") 
    		        break;
    		   
    		    if(token.back() == ','){ // Removes commas
        		    int p = token.find(",");  
        		    token.erase(p);
    		    }
    		    tokens.push_back(token);
    		}
    		
    		// Adds the current line without the comments and commas to the nXn vector wordIn
    		if (tokens.size())		// Skip empty lines
    			wordIn.emplace_back(move(tokens));
        }
    
    inFile.close();
        
    // Save number of lines and erase
    string num = wordIn[0][0];
    wordIn[0].erase(wordIn[0].begin());
    // Save number of memory locations and location
    Number loc;
    double inputLines = loc.CONVERT_TYPE(num) + 2;                      // The line where the number of memory locations is read
    string strMemoryLocations = wordIn[inputLines - 1][0];          // Saves the number of memory locations as a string
    double dblMemoryLocations = loc.CONVERT_TYPE(strMemoryLocations);   // Saves the number of memory locations as a double
    
    vector<string> memoryLocationsVct;
    for (int i = 0; i < dblMemoryLocations; i++){                   // For every memory location store the location
        string memoryLocation  = wordIn[inputLines + i][0];
        memoryLocationsVct.push_back(memoryLocation);
        if(i == (dblMemoryLocations - 1)){
            for (int j = 0; j < dblMemoryLocations; j++){
                wordIn.pop_back(); 
            }
        }
    }
    
    // Adding the memory locations and the value to the DataMemory to be used inside the load and store functions
    string temp;
    for(int i = 0; i < memoryLocationsVct.size(); i++){
         string val;
         string loc;
         int p = (memoryLocationsVct.at(i)).find_first_of("<");
         int t = (memoryLocationsVct.at(i)).find_first_of(">");
         
         (memory.tempLocation).push_back((memoryLocationsVct.at(i)).substr(p+ 1,t-p- 1));
         (memoryLocationsVct.at(i)).erase(p,t-p+1);
         
         p = (memoryLocationsVct.at(i)).find_first_of("<");
         t = (memoryLocationsVct.at(i)).find_first_of(">");
         
         (memory.memVal).push_back((memoryLocationsVct.at(i)).substr(p+ 1,t-p- 1));
         (memoryLocationsVct.at(i)).erase(p,t-p+1);
    }
    
    string instruction;
    // Converting the instructions to binary
    for(size_t i = 0; i < wordIn.size(); i++){
        vector<string> wordInRow(wordIn[i].begin(),wordIn[i].end());
        
        wordInRow.resize(4);
        asmToBin.op = wordInRow.at(0);
        asmToBin.R1 = wordInRow.at(1);
        asmToBin.R2 = wordInRow.at(2);
        asmToBin.R3 = wordInRow.at(3);
        
        instruction = asmToBin.CONVERT_ASM_TO_BINARY();
        
        // Skipping over if the instruction is all zeros.
        if(instruction.substr(0,8) != "00000000"){
            (instructionMemory.instructions).push_back(instruction);
        }
    }
    
    // Creating a variable by reference to hold the intructions from InstructionMemory functional block to keep the main clean and readable
    vector<string>& instructions = instructionMemory.instructions;
 
    // The code below resets the immediate values and labels(lines)
    // Copies the number in the second register position into number3Val for branching. Used to reset number1Val when looping
    asmToBin.number3Val = asmToBin.number1Val;
    
     // Copies the number in the third register position into number4Val for branching. Used to reset number2Val when looping
    asmToBin.number4Val = asmToBin.number2Val;
    
    // Copies isConstantNumber1 into a temp vector. Used to reset isConstantNumber1 when looping
    asmToBin.tempNumber1 = asmToBin.isConstantNumber1;
    
    // Copies isConstantNumber2 into a temp vector. Used to reset isConstantNumber2 when looping
    asmToBin.tempNumber2 = asmToBin.isConstantNumber2;
    
    // Copies branchVal1 into a temp vector. This is used when branching tho access the label(line) for branching on a zero or negative
    asmToBin.tempBranchVal1 = asmToBin.branchVal1; 
    
    // Copies branchVal1 into a temp vector. This is used when branching tho access the label(line) for an unconditional branch
    asmToBin.tempBranchVal2 = asmToBin.branchVal2; 
    
    // Creating a variable by reference to hold the Program Counter from ProgramCounter functional block to keep the main clean and readable
    size_t& PC = programCounter.PC;
    
    // Looping through instructions and passing it into the if statement to call the instruction
    // Program counter(PC)
    for(PC; PC < instructions.size(); PC++){
        // Updating the cycle count
        (clockTime.cycles)++;
        cout << "Number of Cycles: " << clockTime.cycles << endl;
        
        // Fetching the instruction
        string instruction = FETCH(instructions.at(PC));
        clockTime.ACTIVATE_CLOCK(.001); // Running the clock at 100ns
        
        // Decoding the instruction
        // Breaking up the binary into opcode, R1, R2, R3
        string opcode;
        string Ri;
        string Rj;
        string Rk;
        
        // cout << "test1" << endl;
        DECODE(instruction, opcode, Ri, Rj, Rk, registers, asmToBin);
        // cout << "test2" << endl;
        // Activating the clock
        clockTime.ACTIVATE_CLOCK(.001); // Running the clock at 100ns
        
        // Executing the instruction
        EXECUTE(opcode, Ri, Rj, Rk, asmToBin);
        // cout << "test3" << endl;
        // Activating the clock
        clockTime.ACTIVATE_CLOCK(.003); // Running the clock at 300ns
        
        // Writing to memory if the correct contol signals are set
        if((asmToBin.memRead == 1 && asmToBin.memToReg == 1) || asmToBin.memWrite == 1){
            MEMORY(Ri, asmToBin, memory);
            
        // Activating the clock
        clockTime.ACTIVATE_CLOCK(.003); // Running the clock at 300ns
        }
        
        // Writing to the write register if the control signals have been met
        if((asmToBin.memToReg == 0 || asmToBin.memToReg == 1) && asmToBin.regWrite == 1){
            WRITE(Ri, registers, asmToBin);
            
            // Activating the clock
            clockTime.ACTIVATE_CLOCK(.001); // Running the clock at 100ns
        }
        
        // If the instruction is branching then reset immediate values and branching label(line)
        if(asmToBin.branch == true){
            asmToBin.number1Val = asmToBin.number3Val;
            asmToBin.number2Val = asmToBin.number4Val;
            asmToBin.isConstantNumber1 = asmToBin.tempNumber1;
            asmToBin.isConstantNumber2 = asmToBin.tempNumber2;
            asmToBin.branchVal1 = asmToBin.tempBranchVal1;
            asmToBin.branchVal2 = asmToBin.tempBranchVal2;
            
            asmToBin.numberLocation = asmToBin.branchingLocation; // Sets the position in the vector that holds the immediate to the line that the branch went back to
            asmToBin.tempBranch1 = asmToBin.branch; // Holds the value of the branch control signal before it is changed.
            asmToBin.branch = false; // Resetting the branch control signal
            
            PC = asmToBin.branchingLocation - 2; // Setting the pc to the label(line)
        }
    }

    return 0;   
}



