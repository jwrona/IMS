#ifndef DAYTIME_H
#define DAYTIME_H

#include <simlib.h>

#include "main.h"
#include "generator.h"

extern double NEXT_ORD_IN_TIME;
extern DaytimeEnum current_daytime;
extern Generator order_generator;

class Daytime: public Event
{
    void Behavior(void);

    const double DAY_BEGIN_T = 0.0;     //00:00
    const double OPENING_T = 630.0;     //10:30
    const double LUNCH_T = 690.0;       //11:30
    const double LUNCH_END_T = 780.0;   //13:00
    const double DINNER_T = 1080.0;     //18:00
    const double DINNER_END_T = 1260.0; //21:00
    const double CLOSING_T = 1380.0;    //23:00
    const double DAY_END_T = 1440.0;    //24:00
    
    /* average time (in minutes) between two orders income
     * very importatnt numbers
     *
     * 4800 orders per month
     * 160 orders per day
     * 12.5 working hours
     * ------------------
     * 12.8 orders per hour
     * 60 minutes
     * ----------
     * 
     * average time between orders is 4.7 minutes
     */
    const double CLOSED_C = 0.0; //orders don't come
    const double COMMON_C = 6.0;
    const double LUNCH_C = 4.4;
    const double DINNER_C = 3.9;
};
#endif //DAYTIME_H
