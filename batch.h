#ifndef BATCH_H
#define BATCH_H

#include <simlib.h>
#include <cassert>
#include <vector>
#include <iostream>

#include "macros.h"

extern Facility F1;

extern unsigned all_batch_cntr;

/* forward declarations */
class Order;

class Batch: public Process
{
    const unsigned BATCH_CAPACITY = 4;
    const double PREP_TIME_FROM = 2.0;
    const double PREP_TIME_TO = 3.0;

    std::vector<Order*> orders;
    Order *in_facility;
    unsigned id;

    void Behavior(void);

public:
    Batch(Order*);

    void add_order(Order*);
    bool is_full(void);
};

#endif //BATCH_H
