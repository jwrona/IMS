#include "main.h"
#include "generator.h"

Facility chef_fac("Chef");

//unsigned int orders_in_system = 0;
//const unsigned int max_orders_in_system = 10;
//unsigned int refused_orders = 0;
unsigned all_order_cntr = 0;
unsigned all_batch_cntr = 0;

const unsigned char MIN_IN_HOUR = 60;

const double Generator::NEXT_ORD_IN_TIME = 2.0;

int main(void)
{
    /* initialize random number seed */
    RandomSeed(time(nullptr));

    Print("project pizza\n");
    Init(0.0, hour_to_min(2.0));
    (new Generator)->Activate(Exponential(Generator::NEXT_ORD_IN_TIME));
    Run();

    chef_fac.Output();

    return EXIT_SUCCESS;
}

double hour_to_min(double hour)
{
    return (hour * MIN_IN_HOUR);
}
