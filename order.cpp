#include "order.h"

Order::Order(void)
{
    /*
     * order priority assignment in at the specified ratio
     */
    double rnd = Uniform(0.0, 100.0); // 0 - 100 %

    if (rnd <= businness_level)
        Priority = BUSINESS;
    else if (rnd <= (businness_level + bowling_level))
        Priority = BOWLING;
    else
        Priority = OTHERS;
}

void Order::Behavior(void)
{
    std::cout << "*** " << Time << " ***" << std::endl;
    income = Time;
    H((double) Priority);

    std::cout << "pred seize" << std::endl;
    std::cout << '\t' << static_cast<Order*>(F1.in) << std::endl;

    Seize(F1); //seize by the first order in the queue
    std::cout << "po seize" << std::endl;
    std::cout << '\t' << static_cast<Order*>(F1.in) << std::endl;

    //make batch from the top of this facility queue
    //push order which is occupying facility to the batch
    Batch *new_batch = new Batch(static_cast<Order*>(F1.in));

    //fill batch with orders
    //pop from the top of the facility queue, push into batch
    while (!F1.Q1->Empty() && !new_batch->is_full())
    {
	new_batch->add_order(static_cast<Order*>(F1.Q1->GetFirst()));
    }

    //activate batch processing
    new_batch->Activate();

    std::cout << "pred release" << std::endl;
    std::cout << '\t' << static_cast<Order*>(F1.in) << std::endl;
    Release(F1);
    std::cout << "po release" << std::endl;
    std::cout << '\t' << static_cast<Order*>(F1.in) << std::endl;

    //std::cout << "is queue empty? " << F1.Q1->Empty() \
	      << "\tis batch full?" << new_batch->is_full() << std::endl;

    total_time(Time - income);
}

Batch::Batch(Order *ord): Process(HIGHEST_PRIORITY)
{
    in_facility = ord;
    std::cout << "batch = " << this << std::endl;
    add_order(ord);
}

void Batch::Behavior(void)
{
    std::cout << "*** " << Time << " ***" << std::endl;
    Seize(F1);
    std::cout << "batch obsahuje " << orders.size() << std::endl;

    for (unsigned i = 0; i < orders.size(); ++i)
    {
       std::cout << "\tcekam " << i << std::endl;
       Wait(Time + 1.5);
    }

    std::cout << "opoustim varku" << std::endl << std::endl;
    Release(F1); //free for new batch
}

void Batch::add_order(Order *ord)
{
    if (is_full())
        Print("Batch is full.\n");
    else if(std::find(orders.begin(), orders.end(), ord) != orders.end())
    {
        Print("Order allready in batch.\n");
    }
    else
    {
        orders.push_back(ord);
    }
}

bool Batch::is_full(void)
{
    return (orders.size() == batch_capacity);
}
