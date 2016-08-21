#include "generator.h"

void Generator::Behavior()
{
    /* NEXT_ORD_IN_TIME == 0 means that orders will be rejected */
    if (NEXT_ORD_IN_TIME != 0 && !refuse_orders)
    {
	(new Order)->Activate();
	this->Activate(Time + Exponential(NEXT_ORD_IN_TIME));
    }
    else
    {
        /* order refused
        if (refuse_orders)
	    std::cout << "ORDER REFUSED" << std::endl;
	else
	    std::cout << "CLOSED RIGHT NOW" << std::endl;
	*/
    }
}
