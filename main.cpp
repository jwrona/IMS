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

const unsigned char SEC_IN_MIN = 60;
const unsigned char MIN_IN_HOUR = 60;

int main(void)
{
    RandomSeed(time(nullptr)); //initialize random number seed

    Print("project pizza\n");
    Init(0, 30);
    (new Generator)->Activate();
    Run();

    //F1.Output();
    //F2.Output();
    //H.Output();
    //total_time.Output();

    std::cout << "5 minuntes = " << min_to_sec(5.5) << std::endl;
    std::cout << "2 hours = " << hour_to_sec(2.1) << std::endl;
    return EXIT_SUCCESS;
}

double min_to_sec(double min)
{
    return (min * SEC_IN_MIN);
}

double hour_to_sec(double hour)
{
    return (min_to_sec(hour * MIN_IN_HOUR));
}
