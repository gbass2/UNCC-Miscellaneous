#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#define Tick uint64_t

#include <vector>
#include <deque>
#include <iostream>
#include <tuple>
#include <string>
#include "event.hh"
#include "system.hh"
#include "pipeline_reg.hh"

class SimObject {
protected:
    System *sys;

public:
    Tick  currTick() { return sys->currTick(); } // Gets the current system time
    void incTick(Tick t) { sys->incTick(t); } // Increments the system time
    void schedule(Event *e, Tick t) { sys->schedule(e,t); } // Schedules an event
    void reschedule(Event *e, Tick t) { sys->reschedule(e,t); } // Reschedules an event
    void printMEQ() { sys->printMEQ(); }
    virtual void initialize() = 0; // Creates the first event
    SimObject(System *s) : sys(s) {}
};

class Pipeline{
private:
    PipelineReg reg;
    std::string asmOpcode; // Holds the opcode in asm for the incoming instruction
    std::tuple<std::string,std::string,std::string> registers; // Holds the registers for the incoming instruction

    friend class CPU; // Allows Store class to access these private variables
public:
    std::string getAsmOpcode() {return asmOpcode;}
    std::string setAsmOpcode(std::string asmOpcode) {this->asmOpcode = asmOpcode;}
    std::tuple<std::string,std::string,std::string>getRegisters() {return registers;}
    std::string setRegisters(std::tuple<std::string,std::string,std::string> registers) {this->registers = registers;}

};

class CPU: public SimObject{
private:
    // Pipeline stages
    class Fetch : public Event{
    private:
        CPU *cpu;
        Pipeline fetchStage; // Holds the instruction and registers for the fetch stage

    public:
        Fetch(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Fetch";}
        void fetchInstruction(size_t PC); // Gets the instruction from the instruction queue
        Pipeline getFetchStage() { return fetchStage; }
    };

    class Decode : public Event{
    // Finds the data from the registers and passes it to the execution stage to be executed
    private:
        CPU *cpu;
        Pipeline decodeStage; // Holds the instruction and registers for the decode stage

    public:
        Decode(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Decode";}
        void decodeInstruction(); // Prints out the decode stage *****
        void setAsmOpcode(std::string asmOpcode) {this->decodeStage.asmOpcode = asmOpcode;}
        void setRegisters(std::tuple<std::string,std::string,std::string> registers) {this->decodeStage.registers = registers;}
        Pipeline getDecodeStage() { return decodeStage; }
    };

    class Execute : public Event{
    // Passes the incoming registers or memory location to the ALU to be operated
    private:
        CPU *cpu;
        Pipeline executeStage; // Holds the instruction and registers for the execute stage
    public:
        Execute(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Execute";}
        void executeInstruction(); // Prints execute stage *****
        void setAsmOpcode(std::string asmOpcode) {this->executeStage.asmOpcode = asmOpcode;}
        void setRegisters(std::tuple<std::string,std::string,std::string> registers) {this->executeStage.registers = registers;}
        Pipeline getExecuteStage() { return executeStage; }
    };

    class Store : public Event{
    // Store back in memory if needed
    private:
        CPU *cpu;
        Pipeline storeStage; // Holds the instruction and registers for the store stage
    public:
        Store(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Store";}
        void storeInstruction(); // Prints store stage *****
        void setAsmOpcode(std::string asmOpcode) {this->storeStage.asmOpcode = asmOpcode;}
        void setRegisters(std::tuple<std::string,std::string,std::string> registers) {this->storeStage.registers = registers;}
        Pipeline getStoreStage() { return storeStage; }
    };

    class Stall : public Event{
        // Store back in memory if needed
    private:
        CPU *cpu;
    public:
        Stall(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Stall";}
    };

    // Instances of the pipeline stages
    Fetch *f;
    Decode *d;
    Execute *ex;
    Store *s;

    Tick clk;
    Event *e; // Used for scheduling a Tick

public:
    CPU(System *s) : SimObject(s), f(new Fetch(this)), d(new Decode(this)), ex(new Execute(this)), s(new Store(this)) {}

    virtual void initialize() override { // Initialzes MEQ with a fetch event
        schedule(f, currTick());
    }
    void process() {
        std::cout << "processing on Tick " << currTick() << std::endl;
        schedule(e, currTick() + clk);
    }

    // Runs the simulation
    void runSimulation(Tick end);
};

#endif //SIMOBJECT_H
