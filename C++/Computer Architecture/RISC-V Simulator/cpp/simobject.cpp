#include "simobject.hh"
#include <iostream>
void CPU::runSimulation(Tick end){
    clk  = 1;
    while(currTick() < end){
        // while((sys->getMEQ()).begin() != (sys->getMEQ()).end()){
        //     // printMEQ();
        //     if ((sys->getMEQ().front()->getTime()) < currTick())
        //         assert(0);
        //     else if((sys->getMEQ().front()->getTime()) == currTick()){
        //     //
        //     // }
        //     //
        //     // if(currTick() > 1){
        //     //     e = f;
        //     //     f->process();
        //     // }
        //     //
        //     // if (currTick() > 1){
        //     //     e = d;
        //     //     d->process();
        //     // }
        //     //
        //     // e = ex;
        //     // ex->process();
        //     //
        //     // e = s;
        //     // s->process();
        //     }
        //     else
        //         break;
        // }
        incTick(1); // Increments currentTick by amount (t)
    }
}
