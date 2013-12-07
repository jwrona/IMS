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
public:
    enum PriorityEnum
    {
        OTHERS,
        BOWLING,
        BUSINESS,
	REPARATION
    };

private:
    const double BUSINNESS_LEVEL = 1.3; //%
    const double BOWLING_LEVEL   = 9.0; //%
    const double OTHERS_LEVEL    = 89.7; //%

    const double MAX_TIMEOUT_LENGTH = 120.0; //minutes
    const double TIMEOUT_EXP_SLOPE = 5.0;

    double income;
    unsigned id;
    Batch *batch_im_in;

    void Behavior(void);

public:
    Order(bool reparation = false);
    ~Order();

    Timeout *t = nullptr;

    double get_income(void) {return income;};
    unsigned get_id(void) {return id;};
    Timeout* get_timeout(void) {return t;};
    void set_batch(Batch *b) {batch_im_in = b;};
    Batch* get_batch(void) {return batch_im_in;};
    void repare(void);
};

#endif //ORDER_H
