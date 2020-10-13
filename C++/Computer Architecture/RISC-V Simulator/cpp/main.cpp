#include "event.hh"
#include "system.hh"
#include "simobject.hh"
#include "pipeline_reg.hh"

int main(){
    System *sys = new System();
    CPU *cpu = new CPU(sys);
    cpu->initialize();
    cpu->runSimulation(11);

    return 0;
}
