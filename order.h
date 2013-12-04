#ifndef ORDER_H
#define ORDER_H

#ifndef NDEBUG_PRINT
    #define DEBUG(x) do { std::cout << x << "\tid = " \
    << id << "\tPriority = "<< static_cast<unsigned>(Priority) \
    << "\ttime = " << Time << std::endl;} while (0)
#else
    #define DEBUG(x)
#endif //NDEBUG

#include <simlib.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>


extern Facility F1;
extern Facility F2;

extern Histogram H;
extern Histogram total_time;

extern unsigned all_order_cntr;
extern unsigned all_batch_cntr;

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

    void Behavior(void);

public:
    Order(void);
    unsigned id;
};

class Batch: public Process
{
    const unsigned batch_capacity = 4;

    std::vector<Order*> orders;
    Order *in_facility;
    unsigned id;

    void Behavior(void);

public:
    Batch(Order*);

    void add_order(Order*);
    bool is_full(void);
};

#endif //ORDER_H
