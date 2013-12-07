#include "generator.h"

void Generator::Behavior()
{
    if (NEXT_ORD_IN_TIME != 0)
    {
	(new Order)->Activate();
	this->Activate(Time + Exponential(NEXT_ORD_IN_TIME));
    }
}
