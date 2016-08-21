#ifndef FAILURE_PROCESS_H
#define FAILURE_PROCESS_H

#include <simlib.h>

extern Facility oven_fac;
extern unsigned refuse_orders;

class FailureProcess: public Process
{
    const double FAILURE_WAIT_TIME = 300.0;
    void Behavior(void);
};

#endif //FAILURE_PROCESS_H
