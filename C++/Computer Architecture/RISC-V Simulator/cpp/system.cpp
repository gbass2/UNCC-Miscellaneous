#include "system.hh"

void System::schedule(Event *e, Tick t){ // Schedule and event in the MEQ. Throw and error if event already scheduled
    // ???? How are we handling data ????
    // ???? How to do this ????
    // Looping through MEQ to see if the event is already in the MEQ

    // Scheduling event
    e->setTime(t);
    MEQ.push(e);
}

void System::reschedule(Event *e, Tick t){ // Reschedule and event or schedule if not found
    // If found then delete and reschedule at time t
    // else schedule
}
