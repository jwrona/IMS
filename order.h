#ifndef ORDER_H
#define ORDER_H

#include <simlib.h>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "macros.h"


extern Facility F1;

extern Histogram H;
extern Histogram total_time;

extern unsigned all_order_cntr;

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

    void Behavior(void);

public:
    Order(void);
    double get_income(void) {return income;};
    unsigned get_id(void) {return id;};
};

#endif //ORDER_H
