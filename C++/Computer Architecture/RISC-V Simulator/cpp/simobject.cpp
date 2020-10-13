#include "simobject.hh"

// Fetching the instruction and putting it in the Pipeline class. Also printing it out.
void CPU::Fetch::fetchInstruction(size_t PC) { // Retrives the instruction from the instruction queue at the current program counter. Needs restructuring once Instructions class is implemented
    fetchStage.asmOpcode = (fetchStage.reg).instructionQueue.at(PC);
    this->fetchStage.registers = (fetchStage.reg).registers.at(PC);

    std::string temp1 = (fetchStage.reg).instructionQueue.at(PC);
    std::tuple<std::string,std::string,std::string> temp2 = (fetchStage.reg).registers.at(PC);

    std::cout << "Fetch " << temp1 << " " << std::get<0>(temp2) << " " << std::get<1>(temp2) << " " << std::get<2>(temp2) << " cycle: " << cpu->currTick() << std::endl;
}

// Prints the decode stage
void CPU::Decode::decodeInstruction() {
    std::tuple<std::string,std::string,std::string> r = decodeStage.registers;
    std::cout << "Decode " << decodeStage.asmOpcode << " " << std::get<0>(r) << " " << std::get<1>(r) << " " << std::get<2>(r) << " cycle: " << cpu->currTick() << std::endl;
}

// Prints the execute stage
void CPU::Execute::executeInstruction() {
    std::tuple<std::string,std::string,std::string> r = executeStage.registers;
    std::cout << "Execute " << executeStage.asmOpcode << " " << std::get<0>(r) << " " << std::get<1>(r) << " " << std::get<2>(r) << " cycle: " << cpu->currTick() << std::endl;

    // End program if instruction is a halt

    if(executeStage.getAsmOpcode() == "halt")
        exit(0);
}

// Prints the store instruction
void CPU::Store::storeInstruction() {
    std::tuple<std::string,std::string,std::string> r = storeStage.registers;
    std::cout << "Store " << storeStage.asmOpcode << " " << std::get<0>(r) << " " << std::get<1>(r) << " " << std::get<2>(r) << " cycle: " << cpu->currTick() << std::endl;
}

// Main function for running the simulation
void CPU::runSimulation(Tick end){
    size_t loop = 0;
    size_t PC = 0; // Program Counter

    while(!(sys->getMEQ()).empty()){
        printMEQ();
        if ((sys->getMEQ().front()->getTime()) < currTick()){
            std::cout << "Error: Event was scheduled prior to the current time" << std::endl;
            assert(0);
        }

        // Schedules accesses the store stage
        if(!(strcmp(sys->getMEQ().front()->description(), "Store")) && (sys->getMEQ().front()->getTime()) == currTick()){
            s->storeInstruction();
            sys->removeEvent();

        // Schedules and accesses the execute stage
        } if(!(strcmp(sys->getMEQ().front()->description(), "Execute")) && (sys->getMEQ().front()->getTime()) == currTick()){
            ex->executeInstruction();
            s->setAsmOpcode(ex->getExecuteStage().getAsmOpcode());
            s->setRegisters(ex->getExecuteStage().getRegisters());
            sys->removeEvent();
            schedule(s, currTick() + 1);

        // Schedules and access the decode stage
        } if(!strcmp(sys->getMEQ().front()->description(), "Decode") && (sys->getMEQ().front()->getTime()) == currTick()){
            d->decodeInstruction();
            ex->setAsmOpcode(d->getDecodeStage().getAsmOpcode());
            ex->setRegisters(d->getDecodeStage().getRegisters());
            sys->removeEvent();
            schedule(ex, currTick() + 1);

        // Schedules and access the fetch stage
        } if(!(strcmp(sys->getMEQ().front()->description(), "Fetch")) && (sys->getMEQ().front()->getTime()) == currTick()){
            f->fetchInstruction(PC);
            d->setAsmOpcode(f->getFetchStage().getAsmOpcode());
            d->setRegisters(f->getFetchStage().getRegisters());
            sys->removeEvent();
            std::cout << "Fetching the next instruction" << std::endl << std::endl;

            // Scheduling decode for next instruction
            schedule(d, currTick() + 1);
            // Scheduling fetch for next instruction
            schedule(f, currTick() + 1);
        }

        incTick(1); // Increments currentTick by amount (t)

        // Dealing with brancing
        if(d->getDecodeStage().getAsmOpcode() == "bne"){
            PC = -1;
            loop++;
        }
        PC++;

        if (s->getStoreStage().getAsmOpcode() == "bne" && loop == 2) {
            sys->clearMEQ();
            sys->printMEQ();
            ex->setAsmOpcode("halt");
            std::tuple<std::string, std::string, std::string > registers = { "", "", ""};
            ex->setRegisters(registers);
            ex->deschedule();
            sys->schedule(ex, currTick());
        }
    }
}
