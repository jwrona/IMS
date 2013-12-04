#ifndef ORDER_H
#define ORDER_H

#include <simlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

extern Facility F1;
extern Facility F2;

extern Histogram H;
extern Histogram total_time;

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
    //const double others_level    = 70.0; //%

    double income;

    void Behavior(void);

public:
    Order(void);
};

class Batch: public Process
{
    const unsigned batch_capacity = 4;

    std::vector<Order*> orders;
    Order *in_facility;

    void Behavior(void);

public:
    Batch(Order*);

    void add_order(Order*);
    bool is_full(void);
};

#endif //ORDER_H
