#include <simlib.h>
#include <iostream>
#include <chrono>

#include "failure_event.h"
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

/* flag set by failure to ensure all new orders will be
 * immediately refused as they come in */
bool refuse_orders = false;

unsigned orders_in_system_now = 0;
const unsigned MAX_ORDERS_IN_SYSTEM = 10;
//unsigned int refused_orders = 0;
unsigned all_order_cntr = 0;
unsigned all_batch_cntr = 0;

const double START_TIME = 0.0;
const double END_TIME = 1400.0;
DaytimeEnum current_daytime = CLOSED;


/* time between two orders, set by daytime event */
double NEXT_ORD_IN_TIME = 0.0;
/* time between two failures */
double NEXT_FAILURE_IN_TIME = 129600.0; //3 months

int main(void)
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    /* initialize random number seed */
    RandomSeed(seed);

    Init(START_TIME, END_TIME);

    (new Daytime)->Activate();
    (new FailureEvent)->Activate(Time + Exponential(NEXT_FAILURE_IN_TIME));
    Run();

    chef_fac.Output();
    chef_que.Output();
    oven_fac.Output();
    oven_que.Output();
    delivery_store.Output();
    delivery_que.Output();

    return EXIT_SUCCESS;
}
