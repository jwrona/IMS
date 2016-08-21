#ifndef FAILURE_EVENT_H
#define FAILURE_EVENT_H

#include <simlib.h>

extern double NEXT_FAILURE_IN_TIME;

class FailureEvent: public Event
{
    void Behavior(void);
};

#endif //FAILURE_EVENT_H
