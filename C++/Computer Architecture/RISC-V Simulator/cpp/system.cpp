#include "system.hh"
#include <iostream>

std::vector<Event *>::iterator findEvent(Event *e){

}

void System::schedule(Event *e, Tick t){ // Schedules an event into MEQ
    // Adding the event to MEQ
    e->schedule(t);
    MEQ.push_back(e);

    for(auto it = MEQ.begin(); it != MEQ.end(); it++){
        MEQ.insert(it, e);
        return;
    }
}
// 
void System::reschedule(Event *e, Tick t){ // Reschedules an event in MEQ
    assert(t >= currentTick);
    if(e->isScheduled()){
        // MEQ.erase(findEvent(e));
        e->schedule(t);

        for(auto it = MEQ.begin(); it != MEQ.end(); it++){
            MEQ.insert(it, e);
            return;
        }
    }
}

void System::printMEQ(){
    std::cout << "MEQ begin" << std::endl;
    for(size_t i = 0; i < MEQ.size(); i++){
        std::cout << (MEQ.at(i))->getTime() << ":" << (MEQ.at(i))->description() << std::endl;
    }
        std::cout << "MEQ end" << std::endl;
}

void System::removeEvent(){
    Event * temp = MEQ.front();
    temp->deschedule();
    MEQ.pop_front();
}
