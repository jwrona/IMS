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
    income = Time;
    H((double) Priority);

    Seize(F1); //make batch from the top of this facility queue
    {
        std::cout << "obsazuji varku" << std::endl;
	Batch *new_batch = new Batch(static_cast<Order*>(F1.in));

	while (!F1.Q1->Empty() && !new_batch->is_full())
	{
	    std::cout << "length before = " << F1.Q1->Length() << std::endl;
	    new_batch->add_order(static_cast<Order*>(F1.Q1->GetFirst()));
	    std::cout << "length after = " << F1.Q1->Length() << std::endl;
	}

	std::cout << "is queue empty? " << F1.Q1->Empty()
	          << "\tis batch full?" << new_batch->is_full() << std::endl;

	//new_batch->add_order((Order*)F1.in);
	new_batch->Activate();
    }

    total_time(Time - income);
}

Batch::Batch(Order *ord): in_facility(ord)
{
    add_order(ord);
}

void Batch::Behavior(void)
{
    std::cout << "batch obsahuje " << orders.size() << std::endl;

    for (unsigned i = 0; i < orders.size(); ++i)
    {
       std::cout << "\tcekam " << i << std::endl;
       Wait(Exponential(1));
    }

    std::cout << "opoustim varku" << std::endl << std::endl;
    in_facility->Release(F1); //free for new batch
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
