// asm_binary holds the functional blocks and maps for converting between asm and binary
#ifndef ASM_BINARY_H
#define ASM_BINARY_H

#include <vector>
#include <string>

using namespace std;

// Register File Block
class RegisterFile{
  public:
  vector<string> registerInBinary{"00000100","00000101","00000110","00000111","00001000","00001001","00001010","00001011","00001100","00001101","00001110","00001111","00010000","00010001", "00010010","00010011"}; // Bianey represisnation postion of registers
  vector<string> registerInASM{"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"}; 
  vector<string> value{"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"}; // The value of the registers R0-R15
 
  // Used for converting from ASM to binary and back. Used to create the 32 bit instruction string
  vector<string> tempValue{"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"}; // 16 temporarily variables. Used to hold the constant numbers and the branching numbers
  vector<string> tempRegAsm{"R16","R17","R18","R19","R20","R21","R22","R23","R24","R25","R26","R27","R28","R29","R30","R31","R32","R33","R34"}; // ASM represinataion of temporary variables
  vector<string> tempRegBin{"00110000","00110001","00110010","00110011","00110100","00110101","00110110","00110111","00111000","00111001","00111010","00111011","00111100","00111101","00111110","00111111","01000000","01000001","01000010"}; // Bianry representation of temporary variables
  
  // Holds the immediate values after being read from the file waiting to be set
  vector<string> number1Val; // Used to hold the cosntant numbers for the second register position in the instruction
  vector<string> number2Val; // Used to hold the cosntant numbers for the third register position in the instruction
  vector<string> number3Val; // Used to hold the cosntant numbers for the second register position in the instruction
  vector<string> number4Val; // Used to hold the cosntant numbers for the third register position in the instruction
  
  vector<int> RiPos; // Position of the register Ri in the value vector. Used when writing back to the register
  
  // Methods
  string FINDING_REGISTER_FROM_BINARY(string);
  string FINDING_REGISTER_ASM_FROM_BINARY(string);
  string GET_VALUE(string, bool);
  void WRITE_VALUE(string);
};

// Data Memory Block
class DataMemory{
  public:
  vector<string> location{"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"}; // Memory location for loading and storing
  vector<string> memVal; // temporarily holds the value of the register to be loaded. Holds the value after read from the file
  vector<string> tempLocation; // temporarily holds the location of the register to be loaded. Holds the location after read from the file
  
  void setLocationToValue(string memLocation, string memValue);
  string getLocationToValue();
  
  void setValueToLocation(string memLocationm, string memValue);
  string getValueToLocation();
  
  
  // vector<string> location[16000];
  // vector<string> value[16000];
};

// Instruction Memory Block
class InstructionMemory{
  public:
  // Holds the instructions
  vector<string> instructions;
};

// Program Counter Functional Block
class ProgramCounter{
  public:
  // Points to the next instruction to execute
  size_t PC = 0;
};

// Class that holds the map for converting the opcode to binary or ASM
class Opcode{
  protected:
  vector<string> opcodeInBinary{"00011000", "00011001", "00011010", "00011011", "00011100", "00011101", "00011110","00011111", "00100000", "00100001","00100010", "00100011", "00100100","00100101", "00100110", "00100111", "00101000", "00101001", "00101010", "00101011", "00101100", "00101101", "00101110"}; // Binary representation of opcode
  vector<string> opcodeInASM{"SET","LOAD","STORE","MOVE","FADD","FSUB","FNEG","FMUL","FDIV","FLOOR","CEIL","ROUND","FABS","MIN","MAX","POW","EXP","SQRT","B","BZ","BN","NOP","HALT"}; // ASM representation of opcode
                                                                                                                                                                                            
  // Methods
  string FINDING_OPCODE_BINARY_FROM_ASM(string);                                                                                                                                                 
  string FINDING_OPCODE_ASM_FROM_BINARY(string);
};

// The clock rate 
class Clock{
  public:
  int cycles = 0;
  void ACTIVATE_CLOCK(int);
};


// A class used to convert the instruction to Binary or ASM
class AsmBinary : public RegisterFile, public DataMemory, public Opcode{
  public:
  // Used for outputting the asm. Milestone 1
  bool isZero1; // If the instruction does does not use the first number
  bool isZero2; // If the instruction does does not use the second number
  bool isZero3; // If the instruction does does not use the third number
  vector<bool> isNumber1; // Sets the flag true if the number is a branch number in the second register psotion of the instruction
  vector<bool> isNumber2; // Sets the flag true if the number is a branch number in the second register psotion of the instruction
  vector<bool> isNumber3; // Sets the flag true if the number is a branch number in the second register psotion of the instruction
  
  
  vector<bool> isConstantNumber1; // Sets the flag true if the number is an immediate value is in the second register psotion of the instruction
  vector<bool> isConstantNumber2; // Sets the flag true if the number is an immediate value is in the second register psotion of the instruction
  vector<bool> tempNumber1; // Used for temporarily holding isConstantNumber1
  vector<bool> tempNumber2; // Used for temporarily holding isConstantNumber2
  
  vector<string> branchVal1; // Holds the lines to branch back to for branch on negative and branch on zero
  vector<string> branchVal2; // Holds the lines to branch back to for unconditional branch
  
  int iterator = 0; // An iterator thats used to determine where to access the immediate value in the branchVal vector
  int iterator2 = 0;
  
  string forwardValueA; // Holds the value that will be forwarded to the next instruction
  string forwardValueB; // Holds the value that will be forwarded to the next instruction
  
  vector<string> tempBranchVal1; // Holds the lines to branch back to for branch on negative and branch on zero
  vector<string> tempBranchVal2; // Holds the lines to branch back to for unconditional branch
  
  // Branching
  bool tempBranch1 = false;
  int branchingLocation; // Used to hold the line to branch back to for a branch on negative
  int numberLocation = 0; // Used in the set or power function. Used as an iterator for accessing the immediate values
  
  // Control Signals
  bool branch = false;
  bool reg2Loc = false; 
  bool memRead = false;
  bool memToReg = false;
  bool aluOp = false;
  bool memWrite = false;
  bool aluSrc = false;
  bool regWrite = false;
  
  bool calledSub = false; // Boolean flag for determining if the subtract function needs to be called inside the add function
  bool calledAdd = false; // Boolean flag for determining if the subtract function needs to be called inside the add function
  
  // Forward boolean
  bool forwardRjExecute = false; //Boolean to determine if the result is to forwarded to the next instruction if Rj is dependent on the previous Ri
  bool forwardRjMem = false; //Boolean to determine if the result is to forwarded to the next instruction if Rj is dependent on the previous Ri
  bool forwardRjWrite = false; //Boolean to determine if the result is to forwarded to the next instruction if Rj is dependent on the previous Ri
  bool forwardRkExecute = false; // Boolean to determine if the result is to forwarded to the next instruction if Rk is dependent on the previous Ri
  bool forwardRkMem = false; // Boolean to determine if the result is to forwarded to the next instruction if Rk is dependent on the previous Ri
  bool forwardRkWrite = false; // Boolean to determine if the result is to forwarded to the next instruction if Rk is dependent on the previous Ri
  bool forwardA = false; // Boolean to determine if the forwardedValue string should equal the alu result and forwarded for Rj
  bool forwardB = false; // Boolean to determine if the forwardedValue string should equal the alu result and forwarded for Rk
  

  
  // Methods
  string storedValueASM;
  string storedValueBinary;
  string op, R1, R2, R3;
  string CONVERT_ASM_TO_BINARY();
  string CONVERT_BINARY_TO_ASM(string, int &, int &);
};
 
#endif