#include "timeout.h"
#include "order.h"
#include "batch.h"

Timeout::Timeout(Order *o, double dt): Id(o)
{
    Activate(Time + dt);
}

void Timeout::Behavior(void)
{
    std::cout << "vyprsel casovac objednavce " << Id->get_id() \
    << "\tv case " << Time << std::endl;

    Batch* b = nullptr;
    if ((b = Id->get_batch()) != nullptr)
        b->remove_order(Id);

    Id->Cancel();
    Cancel();
}
