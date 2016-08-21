#include "timeout.h"
#include "order.h"
#include "batch.h"

Timeout::Timeout(Order *o, double dt): Id(o)
{
    Activate(Time + dt);
}

void Timeout::Behavior(void)
{
    //std::cout << "TIMER EXPIRED FOR " << Id->get_id() << std::cout;

    Batch* b = nullptr;
    if ((b = Id->get_batch()) != nullptr)
    {
        /* order is in batch allready, cancel will be executed
	 * in batch */
        b->remove_order(Id);
    }
    else
    {
        /* process not in batch yet */
        Id->Cancel();
    }

    Cancel();
}
