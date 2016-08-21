#ifndef BATCH_H
#define BATCH_H

#include <simlib.h>
#include <cassert>
#include <vector>
#include <iostream>

#include "macros.h"

extern Facility chef_fac;
extern Facility oven_fac;
extern Store delivery_store;

extern unsigned all_batch_cntr;

/* forward declarations */
class Order;

class Batch: public Process
{
    const unsigned BATCH_CAPACITY = 4; //orders

    const double PREP_TIME_FROM = 4.0; //minutes
    const double PREP_TIME_TO = 5.0; //minutes
    const double PREP_ERR_RATE = 1.0; //%

    const double BAKING_TIME = 5.0; //minutes
    const double BAKING_ERR_RATE = 1.0; //%

    const double DELIV_TIME_FROM = 25.0; //minutes
    const double DELIV_TIME_TO = 35.0; //minutes

    std::vector<Order*> orders;
    //std::vector<Order*> removed_orders;
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
