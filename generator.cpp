#include "generator.h"

void Generator::Behavior()
{
    (new Order)->Activate();
    this->Activate(Time + Exponential(NEXT_ORD_IN_TIME));
}
