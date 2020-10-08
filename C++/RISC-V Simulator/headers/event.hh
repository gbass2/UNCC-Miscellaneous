#ifndef EVENT_H
#define EVENT_H

#include <cstdint>
#include <tuple>
#include <string>

#define Tick uint64_t

class Event{
private:
    Tick time; // Time that the event was inserted into the MEQ
    std::tuple<std::string, std::string, std::string> data; // The data for the event, such as: F4, F0, F2


public:
    Event() {};
    void setTime(Tick t){ time = t; }
    Tick getTime() { return time; }
    virtual void process() = 0;
};

#endif // EVENT_H
