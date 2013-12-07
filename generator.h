#ifndef GENERATOR_H
#define GENERATOR_H

#include <simlib.h>
#include "order.h"

extern double NEXT_ORD_IN_TIME;

class Generator: public Event
{
    void Behavior();
};

#endif //GENERATOR_H
