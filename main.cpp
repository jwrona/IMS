#include "main.h"
#include "generator.h"

Facility F1("F1");
Facility F2("F2");

Histogram H("H", 0, 1, 10);
Histogram total_time("Total time", 0, 100, 10);

//unsigned int orders_in_system = 0;
//const unsigned int max_orders_in_system = 10;
//unsigned int refused_orders = 0;
unsigned all_order_cntr = 0;
unsigned all_batch_cntr = 0;

const unsigned char MIN_IN_HOUR = 60;

const double Generator::NEXT_ORD_IN_TIME = 2.0;

int main(void)
{
    RandomSeed(time(nullptr)); //initialize random number seed

    Print("project pizza\n");
    Init(0.0, 200.0);
    (new Generator)->Activate(Exponential(Generator::NEXT_ORD_IN_TIME));
    Run();

    //F1.Output();
    //F2.Output();
    //H.Output();
    //total_time.Output();

    return EXIT_SUCCESS;
}

double hour_to_min(double hour)
{
    return (hour * MIN_IN_HOUR);
}
