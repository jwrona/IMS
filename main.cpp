#include <ctime>
#include <simlib.h>
#include "generator.h"
#include "order.h"

Facility F1("F1");
Facility F2("F2");

Histogram H("H", 0, 1, 10);
Histogram total_time("Total time", 0, 100, 10);

//unsigned int orders_in_system = 0;
//const unsigned int max_orders_in_system = 10;
//unsigned int refused_orders = 0;
unsigned all_order_cntr = 0;
unsigned all_batch_cntr = 0;

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
/*
    for (simlib3::Queue::iterator iter = F1.Q1->begin(), end = F1.Q1->end();
         iter != end; ++iter)
    {
        std::cout << (unsigned int) F1.Q1->Get(iter)->Priority << std::endl;
    }
*/
    return EXIT_SUCCESS;
}
