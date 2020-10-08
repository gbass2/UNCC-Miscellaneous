#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include <vector>
#include "event.hh"
#include "system.hh"
#include "pipeline_reg.hh"

class SimObject{
protected:
    System *sys;
    uint64_t  currTick() { return sys->currTick(); }
    void schedule(Event *e, Tick t) { sys->schedule(e,t); }
    void reschedule(Event *e, Tick t) { sys->reschedule(e,t); }

public:
    SimObject(System *s) : sys(s) {}
};

class Pipeline : public SimObject{
private:
    PipelineReg *reg; // Instance of PipelineReg
    // next; // Pointer to the next pipeline stage

public:
    // void setNext(); // Sets the next stage in the pipeline. may not be neccessary

};

class CPU : public SimObject{
private:
    std::vector<Pipeline> dataPath; // Figure out what this is for

    // Pipeline stages
    class Fetch : public Pipeline{
        // Pass in an event and fetch stage
        // Fetches the instruction and values
    };

    class Decode : public Pipeline{
    };

    class Execute : public Pipeline{
    private:
        friend class ALU; // Allows ALU to access Executes variables

    public:
        // Functions for executing the instruction. like add, branch, etc
    };

    class Store : public Pipeline{
        // Store back in memory if needed
    public:
        void FSD(); // Stores a value from a register into a memory location
    };

    template <typename T>
    class ALU{
    public:
        double FADD_d(double, double); // Adds 2 floating point values
        double FLD(double, double); // Loads a value from memory into a register
        T ADDI(T,T); // Adds an immediate value to a  memory location's value and stores it back in it
        void BNE(); // checks to see if a branch needs to be taken
        void stall(); // Wastes a clock cycle
    };

    Fetch *f;
    Decode *d;
    Execute *ex;
    Store *s;
};

#endif //SIMOBJECT_H
