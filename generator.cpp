#include "generator.h"

void Generator::Behavior()
{
    (new Order)->Activate();
    //this->Activate(Time + Uniform(0.0, act_time));
    this->Activate(Time + 1);
}
