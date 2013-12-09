#include <iostream>
#include <cmath>

#include "daytime.h"

void Daytime::Behavior(void)
{
    double day_time = fmod(Time, DAY_END_T); //in minutes
    //std::cout<<"time = "<<Time<<" day_time = "<<day_time<<std::endl;

    if (day_time >= DAY_BEGIN_T && day_time < OPENING_T)
    {  //closed
        NEXT_ORD_IN_TIME = CLOSED_C;
	current_daytime = CLOSED;
	//std::cout<<"MORNING CLOSED, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (OPENING_T - day_time));
    }
    else if (day_time >= OPENING_T && day_time < LUNCH_T)
    {  //opened
        NEXT_ORD_IN_TIME = COMMON_C;
	current_daytime = COMMON;
	//std::cout<<"OPENED, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (LUNCH_T - day_time));
    }
    else if (day_time >= LUNCH_T && day_time < LUNCH_END_T)
    {  //lunch
        NEXT_ORD_IN_TIME = LUNCH_C;
	current_daytime = LUNCH;
	//std::cout<<"LUNCH, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (LUNCH_END_T - day_time));
    }
    else if (day_time >= LUNCH_END_T && day_time < DINNER_T)
    {  //opened
        NEXT_ORD_IN_TIME = COMMON_C;
	current_daytime = COMMON;
	//std::cout<<"AFTER LUNCH, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (DINNER_T - day_time));
    }
    else if (day_time >= DINNER_T && day_time < DINNER_END_T)
    {  //dinner
        NEXT_ORD_IN_TIME = DINNER_C;
	current_daytime = DINNER;
	//std::cout<<"DINNER, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (DINNER_END_T - day_time));
    }
    else if (day_time >= DINNER_END_T && day_time < CLOSING_T)
    {  //opened
        NEXT_ORD_IN_TIME = COMMON_C;
	current_daytime = COMMON;
	//std::cout<<"AFTER DINNER, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (CLOSING_T - day_time));
    }
    else if (day_time >= CLOSING_T && day_time <= DAY_END_T)
    {  //closed
        NEXT_ORD_IN_TIME = CLOSED_C;
	current_daytime = CLOSED;
	//std::cout<<"EVENING CLOSED, time = "<<Time<<" day_time = "<<day_time<<std::endl;
	Activate(Time + (DAY_END_T - day_time));
    }
    else
    {  //what did I miss?
        assert(false);
    }

    order_generator.Activate();
}
