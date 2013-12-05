#ifndef GENERATOR_H
#define GENERATOR_H

#include <simlib.h>
#include "order.h"

class Generator: public Event
{
    void Behavior();

public:
    static const double NEXT_ORD_IN_TIME;
};

#endif //GENERATOR_H
