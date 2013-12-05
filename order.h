#ifndef ORDER_H
#define ORDER_H

#include <simlib.h>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "macros.h"

extern Facility chef_fac;

extern unsigned all_order_cntr;

/* forward declarations */
class Timeout;
class Batch;

class Order: public Process
{

    enum PriorityEnum
    {
        OTHERS,
        BOWLING,
        BUSINESS
    };

    const double businness_level = 10.0; //%
    const double bowling_level   = 20.0; //%
    const double others_level    = 70.0; //%

    double income;
    unsigned id;
    Timeout *t;
    Batch *batch_im_in;

    void Behavior(void);

public:
    Order(void);
    double get_income(void) {return income;};
    unsigned get_id(void) {return id;};
    Timeout* get_timeout(void) {return t;};
    void delete_timeout(void);
    void set_batch(Batch *b) {batch_im_in = b;};
    Batch* get_batch(void) {return batch_im_in;};
};

#endif //ORDER_H
