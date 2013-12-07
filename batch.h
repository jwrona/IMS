#ifndef BATCH_H
#define BATCH_H

#include <simlib.h>
#include <cassert>
#include <vector>
#include <iostream>

#include "macros.h"

extern Facility chef_fac;

extern unsigned all_batch_cntr;

/* forward declarations */
class Order;

class Batch: public Process
{
    const unsigned BATCH_CAPACITY = 4;
    const double PREP_TIME_FROM = 2.0;
    const double PREP_TIME_TO = 3.0;
    const double PREP_ERR_RATE = 50.0; //%

    std::vector<Order*> orders;
    std::vector<Order*> removed_orders;
    unsigned id;

    void Behavior(void);

public:
    Batch(Order*);

    void add_order(Order*);
    void remove_order(Order*);
    bool is_full(void);
    bool is_empty(void);
};

#endif //BATCH_H
