#include "failure_event.h"
#include "failure_process.h"

void FailureEvent::Behavior(void)
{
    /* create and activate failure process to deal with it */
    (new FailureProcess)->Activate();

    /* activate failure again in future */  
    Activate(Time + Exponential(NEXT_FAILURE_IN_TIME));
}
