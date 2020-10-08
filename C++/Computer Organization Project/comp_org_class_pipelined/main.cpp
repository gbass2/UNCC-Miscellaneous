///-----------------------------------------------------------------
///   Class:          ECGR 3183 Computer Organization 
///   Description:    Simulating how a processor executes instructions
///   Author:         Grayson Bass, Landon Gibson, Sam Xu            
///   Name:           Comp Org Project Pipeline          Date: 4/28/2020 
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
        int countDashesAtStart = 0;
        
        // Fetching the instruction
        // Trying to read word by word. If a "--" is found then skip to the next line
        // The line read is added to an nXn vector wordIn to store the contents of the file
    	while (getline(inFile, line)){
    		istringstream ls(line);
    		string token; // The current word read from the file
    		int count = 0;
    		
    		// Loops until the last line of the file
    		while ( ls >> token ){ 
    		    // Removes comments
    		    if(count == 0 && token == "--"){
    		        countDashesAtStart++;
    		        break;
    		    }
    		    else if(token == "--")
    		        break;
    		   
    		    if(token.back() == ','){ // Removes commas
        		    int p = token.find(",");  
        		    token.erase(p);
    		    }
    		    tokens.push_back(token);
    		    count++;
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
    double inputLines = loc.CONVERT_TYPE(num) + 2; //- countDashesAtStart;                      // The line where the number of memory locations is read
   
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
    
    int nopCount = 0; // Holds the amount of nops that were added instructions;
    
    // Creating a variable by reference to hold the intructions from InstructionMemory functional block to keep the main clean and readable
    vector<string>& instructions = instructionMemory.instructions;
    
    // Schedule nops
    for(size_t i = 0; i < instructions.size(); i++){
        string nop = "00101101000000000000000000000000";
        if(((instructions.at(i)).substr(0,8) == "00011001" && ((instructions.at(i)).substr(8,8) == ((instructions.at(i+1)).substr(16,8)) || (instructions.at(i)).substr(8,8) == ((instructions.at(i+1)).substr(24,8))))){
            instructions.insert(instructions.begin() + i + 1, nop);
            nopCount++;
        }
    }

    // scheduling the instructions
    int col = 4 + instructions.size(); // This is length of the graph. This is how many cycles are to be executed
    int row = instructions.size(); // This how many instructions are to be executed in the pipeline
    vector<vector<string>> pipeline(row, vector<string>(col, " ")); 
    
    // Filling in the vector with FDXMW as individual strings in each row/col
    for(size_t i = 0; i < row; i++){
        pipeline[i][i]   = "F";  
        pipeline[i][i+1] = "D";  
        pipeline[i][i+2] = "X";  
        pipeline[i][i+3] = "M";  
        pipeline[i][i+4] = "W";  
    }

 
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
    
    // Variables to hold the different values once decoded
    string opcode;
    string Ri;
    string Rj;
    string Rk;
    
    // Holds all the values of Ri and Rj for the write stages to access the previous values
    vector<string> RiPrev(col); 
    vector<string> RjPrev(col);
    
    // Holds the control signals for PC -1 for the memory and write back stages
    vector<bool> memToRegPrev(col);
    vector<bool> memWritePrev(col);
    vector<bool> regWritePrev(col);
    vector<bool> memReadPrev(col);
    vector<bool> memToReg(col);
    
    // Looping through instructions and passing it into the if statement to call the instruction
    // Program counter(PC)
    for(size_t cycle = 0; cycle < col; cycle++){
        // Updating the cycle count. Cycles hold the number of cycles that have been ran
        (clockTime.cycles)++;
        cout << "Number of Cycles: " << clockTime.cycles << endl;
        clockTime.ACTIVATE_CLOCK(.001); // Activating the clock each cycle
        PC = 0;
        for(PC; PC < row; PC++){
            if(pipeline[PC][cycle] != " "){
                
                // Fetching the instruction
                if(pipeline[PC][cycle] == "F"){
                    cout << endl << "[Fetch Stage]" << endl;
                    string instruction = FETCH(instructions.at(cycle));
                    cout << "instruction: " << instructions.at(PC) << endl << endl;
                }
                    
                // Decoding the instruction
                if(pipeline[PC][cycle] == "D"){
                    cout << endl << "[Decode Stage]" << endl;
                    cout << "instruction: " << instructions.at(PC) << endl << endl;

                    DECODE(instructions.at(cycle - 1), opcode, Ri, Rj, Rk, registers, asmToBin);
                
                    // Keeping the previous values for the control signals for writing back to memory and registers
                    memToRegPrev.at(cycle) = asmToBin.memToReg;
                    memWritePrev.at(cycle) = asmToBin.memWrite;
                    regWritePrev.at(cycle) = asmToBin.regWrite;
                    memReadPrev.at(cycle) = asmToBin.memRead;
                    memToRegPrev.at(cycle) = asmToBin.memToReg;
                    // Activating the clock
                    clockTime.ACTIVATE_CLOCK(.001); // Running the clock at 100ns
                }
                
                // Executing the instruction
                if(pipeline[PC][cycle] == "X"){
                     cout << endl << "[Execute Stage]" << endl;
                     cout << "instruction: " << instructions.at(PC) << endl << endl;
                    
                    // Determining if need to forward
                    if((instructions.at(PC)).substr(0,8) != "00101110"){    
                        if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(16,8) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(24,8)){
                            // cout << "endl1" << endl;
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(16,8)){
                                // cout << "endl" << endl;
                                asmToBin.forwardA = 1;
                            }
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(24,8)){
                                asmToBin.forwardB = 1;
                            }
                            
                        }else if((instructions.at(PC + 1)).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8)){
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8)){
                                asmToBin.forwardA = 1;
                            }
                        }else{
                            asmToBin.forwardA = 0;
                            asmToBin.forwardB = 0;
                        }
                    }
                    
                    EXECUTE(opcode, Ri, Rj, Rk, asmToBin, memory, clockTime);
            
                    // Retrieving the values for PC -1. So when We write back to a register or memory the correct control signals are retrieved
                    RiPrev.at(cycle) = Ri;
                    RjPrev.at(cycle) = Rj;
                    
                    if((instructions.at(PC)).substr(0,8) != "00101110"){
                        if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(16,8) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(24,8)){
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(16,8)){
                                asmToBin.forwardRjExecute = 1;
                            }
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(24,8)){
                                asmToBin.forwardRkExecute = 1;
                            }
                        }
                        else if(((instructions.at(PC + 1).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8)) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8))){
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 1)).substr(8,8)){
                                asmToBin.forwardRjExecute = 1;
                            }
                        }else{
                            asmToBin.forwardRjExecute = 0;
                            asmToBin.forwardRkExecute = 0;
                            asmToBin.forwardA = 0;
                            asmToBin.forwardB = 0;
                            }
                        }

                    // Activating the clock
                    clockTime.ACTIVATE_CLOCK(.003); // Running the clock at 300ns
                }
        
                // Writing to memory if the correct contol signals are set
                if(pipeline[PC][cycle] == "M"){
                    cout << endl << "[Memory Stage]" << endl;
                    cout << "instruction: " << instructions.at(PC) << endl << endl;
                        
                    if(memReadPrev.at(cycle - 2) == 1 && memToRegPrev.at(cycle - 2) == 1){
                        if((instructions.at(PC)).substr(0,8) != "00101110"){    
                           if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                if(((instructions.at(PC + 1)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC + 1)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))) && (asmToBin.forwardRjExecute == 1 || asmToBin.forwardRkExecute == 1)){
                                }else{
                                    if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)))
                                        asmToBin.forwardA = 1;
                                    if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8)))
                                        asmToBin.forwardB = 1;
                                }
                            }
                            else if(((instructions.at(PC + 1).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8))){
                                if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)){
                                    asmToBin.forwardRjExecute = 1;
                                 }
                            }else{
                                asmToBin.forwardA = 0;
                                asmToBin.forwardB = 0;
                            }
                        }
                        
                        MEMORY(RiPrev.at(cycle - 1), asmToBin, memory, memReadPrev.at(cycle - 2), memToRegPrev.at(cycle - 2), memWritePrev.at(cycle - 2));
                        
                        if((instructions.at(PC)).substr(0,8) != "00101110"){
                            // Retrieving the values for PC - 2. So when We can foward fromm the memory to the next alu instruction
                            if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                if((instructions.at(PC + 1)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC + 1)).substr(8,8) == (instructions.at(PC + 2).substr(24,8)) && (asmToBin.forwardRjExecute == 1 || asmToBin.forwardRkExecute == 1)){
                                }else{
                                    if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8))){
                                        asmToBin.forwardRjMem = 1;
                                    }
                                    
                                    if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                        asmToBin.forwardRkMem = 1;
                                    }
                                }
                            }
                            else if(((instructions.at(PC + 1).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8))){
                                if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)){
                                    asmToBin.forwardRjExecute = 1;
                                }
                            }else{
                                // Reseting the forward booleans
                                asmToBin.forwardRjMem = 0;
                                asmToBin.forwardRkMem = 0;
                                asmToBin.forwardA = 0;
                                asmToBin.forwardB = 0;
                            }
                             // Activating the clock
                            clockTime.ACTIVATE_CLOCK(.003); // Running the clock at 300ns
                        }
                    }else if(memWritePrev.at(cycle - 2) == 1){
                        MEMORY(RjPrev.at(cycle - 1), asmToBin, memory, memWritePrev.at(cycle - 2), memReadPrev.at(cycle - 2), memToRegPrev.at(cycle - 2));
                        // Activating the clock
                        clockTime.ACTIVATE_CLOCK(.003); // Running the clock at 300ns
                    }
                }
                    
                // Writing to the write register if the control signals have been met
                if(pipeline[PC][cycle] == "W"){
                    cout << endl << "[Write Stage]" << endl;
                    cout << "instruction: " << instructions.at(PC) << endl <<  endl;
            
                    if((memToRegPrev.at(cycle - 3) == 0 || memToRegPrev.at(cycle - 3) == 1) && regWritePrev.at(cycle - 3) == 1){
                        if((instructions.at(PC)).substr(0,8) != "00101110"){
                            if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                if((instructions.at(PC + 1)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC + 1)).substr(8,8) == (instructions.at(PC + 2).substr(24,8)) && (asmToBin.forwardRjExecute == 1 || asmToBin.forwardRkExecute == 1)){
                                }else{
                                    if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8))){
                                        asmToBin.forwardA = 1;
                                    }
                                    if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8)))
                                        asmToBin.forwardB = 1;
                                }
                            }
                            else if(((instructions.at(PC + 1).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8))){
                                if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)){
                                    asmToBin.forwardRjExecute = 1;
                                }
                            }else{
                                asmToBin.forwardA = 0;
                                asmToBin.forwardB = 0;
                            }
                        }
                        
                        WRITE(RiPrev.at(cycle - 2), registers, asmToBin);
                            
                        if((instructions.at(PC)).substr(0,8) != "00101110"){
                            // Retrieving the values for PC - 2. So when We can foward from the write to the next alu instruction
                            if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                if((instructions.at(PC + 1)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8)) || (instructions.at(PC + 1)).substr(8,8) == (instructions.at(PC + 2).substr(24,8)) && (asmToBin.forwardRjExecute == 1 || asmToBin.forwardRkExecute == 1)){
                                
                                }else{
                                    
                                    if((instructions.at(PC)).substr(8,8) ==  (instructions.at(PC + 2).substr(16,8))){
                                        if(asmToBin.forwardRjMem != 1)
                                            asmToBin.forwardRjWrite = 1;                                    }
                                    if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2).substr(24,8))){
                                        if(asmToBin.forwardRkMem != 1)
                                            asmToBin.forwardRkWrite = 1;
                                    }
                                }
                            }
                        else if(((instructions.at(PC + 1).substr(0,8) == "00101100" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)) || (instructions.at(PC + 1)).substr(0,8) == "00101011" && (instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8))){
                            if((instructions.at(PC)).substr(8,8) == (instructions.at(PC + 2)).substr(8,8)){
                                asmToBin.forwardRjExecute = 1;
                            }
                        }else{
                            asmToBin.forwardRjWrite = 0;
                            asmToBin.forwardRkWrite = 0;
                            asmToBin.forwardA = 0;
                            asmToBin.forwardB = 0;
                        }
                            // Activating the clock
                            clockTime.ACTIVATE_CLOCK(.001); // Running the clock at 100ns
                        }
                    }
                }
            }
        }
    }

    return 0;   
}



