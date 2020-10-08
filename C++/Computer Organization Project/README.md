This project was a semester long team Project in Computer Organization.
The goal with this project was to desgn and implement a basic RISC-V processor at a bit level and write a report detailing the design process.

The following was implemented in the project:

    - Read a program from a file and execute the instructions in the file.
    - Convert the assembly code from the file into binary and split it up into opcode and registers.
    - Registers for holding data for ALU operations.
    - Memory to hold data and are accessed from a load or store.
    - A program counter that points to the nexted instruction to be excuted.
    - A clock to hold the 
    - An ALU to excute the instructions during the execution stage.
    - The data was stored as single precision floating point.
    - Some operations were done at the bit level.
    - A five stage pipeline that included: Fetch, Decode, Execute, Memory, Write Back.
      - Fetch the instruction from the file.
      - Decode the instruction by breating up the 32 bit binary instruction into opcode and registers and gathering the data to be executed.
      - Excecute the instruction some at bit level.
      - Access Memory whether a store or a load.
      - Write back to the register once the operation is finished.
      
    - Control signals for the flow of the pipeline.
    - Branching was implemented but branch prediction was not finished for the final submission.
    
The comp_org_class_pipelined folder contains the pipelined version of the project.
The comp_org_class_single_cycle folder contains the non-pipelined version of the project.

     
