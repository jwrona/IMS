#include <simlib.h>
#include <iostream>
#include <chrono>

#include "main.h"
#include "generator.h"
#include "daytime.h"

Queue chef_que("Chef");
Facility chef_fac("Chef", &chef_que);

Queue oven_que("Oven");
Facility oven_fac("Oven", &oven_que);

const unsigned DELIVERY_CARS = 3;
Queue delivery_que("Delivery");
Store delivery_store("Delivery", DELIVERY_CARS, &delivery_que);

Generator order_generator;

//unsigned int orders_in_system = 0;
//const unsigned int max_orders_in_system = 10;
//unsigned int refused_orders = 0;
unsigned all_order_cntr = 0;
unsigned all_batch_cntr = 0;

const double START_TIME = 0.0;
const double END_TIME = 1440.0;
DaytimeEnum current_daytime = CLOSED;


/* time between two orders income, set by daytime event */
double NEXT_ORD_IN_TIME = 0.0;

int main(void)
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    /* initialize random number seed */
    RandomSeed(seed);

    Init(START_TIME, END_TIME);

    (new Daytime)->Activate();
    Run();

    chef_fac.Output();
    chef_que.Output();
    oven_fac.Output();
    oven_que.Output();
    delivery_store.Output();
    delivery_que.Output();

    return EXIT_SUCCESS;
}
