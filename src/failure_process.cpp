#include <iostream>

#include "failure_process.h"

void FailureProcess::Behavior(void)
{
    Seize(oven_fac, 1);
    //std::cout << "PORUCHA PECE " << Time << std::endl;
    refuse_orders = true;
    Wait(Exponential(FAILURE_WAIT_TIME));
    Release(oven_fac);
    refuse_orders = false;
    //std::cout << "KONEC PORUCHY PECE " << Time << std::endl;
}
