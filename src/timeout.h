#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <simlib.h>

#include "macros.h"

/* forward declarations */
class Order;

class Timeout: public Event
{
   Order *Id;

    void Behavior(void);

public:
    Timeout(Order*, double);
    ~Timeout() {};
};

#endif //TIMEOUT_H
