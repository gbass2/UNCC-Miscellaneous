#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#define Tick uint64_t

#include <vector>
#include <iostream>
#include "event.hh"
#include "system.hh"
#include "pipeline_reg.hh"

class SimObject{
protected:
    System *sys;
    Tick  currTick() { return sys->currTick(); } // Gets the current system time
    void incTick(Tick t) { sys->incTick(t); } // Increments the system time
    void schedule(Event *e, Tick t) { sys->schedule(e,t); } // Schedules an event
    void reschedule(Event *e, Tick t) { sys->reschedule(e,t); } // Reschedules an event
    void printMEQ() { sys->printMEQ(); }
    virtual void initialize() = 0; // Creates the first event

public:
    SimObject(System *s) : sys(s) {}
};

class Pipeline : public SimObject{
private:
    
public:
    PipelineReg *reg; // Instance of PipelineReg
    Pipeline(System *s) : SimObject(s)  {}
};

class CPU: public SimObject{
private:
    friend class System;
    // Pipeline stages
    class Fetch : public Event{
    private:
        CPU *cpu;
    public:
        Fetch(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Fetch";}

    };

    class Decode : public Event{
        // Finds the data from the registers and passes it to the execution stage to be executed
    private:
        CPU *cpu;
    public:
        Decode(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Decode";}
    };

    class Execute : public Event{
        // Passes the incoming registers or memory location to the ALU to be operated
    private:
        CPU *cpu;
    public:
        Execute(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Execute";}
    };

    class Store : public Event{
        // Store back in memory if needed
    private:
        CPU *cpu;
    public:
        Store(CPU *c) : Event(), cpu(c) {}
        virtual void process() override {cpu->process();}
        virtual const char* description() override {return "Store";}
    public:
        void FSD(); // Stores a value from a register into a memory location
    };

    Fetch *f;
    Decode *d;
    Execute *ex;
    Store *s;

    // std::vector<Pipeline> dataPath; // Figure out what this is for
    Tick clk;
    Event *e; // Used for scheduling

public:
    CPU(System *s) : SimObject(s), f(new Fetch(this)), d(new Decode(this)), ex(new Execute(this)), s(new Store(this)) {}
    virtual void initialize() override {
        schedule(f, currTick());
    }

    void process() {
        std::cout << "processing on Tick " << currTick() << std::endl;
        schedule(e,currTick() + clk);
    }

    void runSimulation(Tick end);
};

#endif //SIMOBJECT_H
