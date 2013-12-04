#ifndef GENERATOR_H
#define GENERATOR_H

#include <simlib.h>
#include "order.h"

class Generator: public Event
{
    const double act_time = 10.0;
    void Behavior();
};

#endif //GENERATOR_H
