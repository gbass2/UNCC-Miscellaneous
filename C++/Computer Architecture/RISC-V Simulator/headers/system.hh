#ifndef SYSTEM_H
#define SYSTEM_H

#include <queue>
#include <cstdint>
#include "event.hh"

#define Tick uint64_t

class System{
private:
    Tick currentTick; // Holds the current run time
    std::queue<Event *> MEQ; // Master Event Queue

public:
    System() : currentTick(0) {}
    Tick currTick(){ return currentTick; }
    // Might need function to set time
    void schedule(Event *e, Tick t); // Schedule and event in the MEQ. Throw and error if event already scheduled
    void reschedule(Event *e, Tick t); // Reschedule an event or schedule if not found
};

#endif // SYSTEM_H
