#include "order.h"

Order::Order(void)
{
    assert((businness_level+ bowling_level + others_level) == 100.0);
    id = all_order_cntr++;

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
    DEBUG("***O:\t\t\t");

    income = Time;
    H((double) Priority);

    /* seize by the first Order in the queue */
    Seize(F1);
    DEBUG("O: zarizeni zabrano\t");

    /*
     * create batch
     * push order which is occupying facility to the batch
     */
    Batch *new_batch = new Batch(static_cast<Order*>(F1.in));

    /*
     * fill batch with orders
     * pop from the top of the facility queue, push into batch
     */
    DEBUG("O: fronta pred pushem:\t" << F1.Q1->Length());
    while (!F1.Q1->Empty() && !new_batch->is_full())
	new_batch->add_order(static_cast<Order*>(F1.Q1->GetFirst()));

    DEBUG("O: fronta po pushi:\t" << F1.Q1->Length());

    //std::cout << "fronta pred insertem: " << F1.Q1->Length() << std::endl;
    F1.Q1->Insert(new_batch);
    //std::cout << "fronta po insertu : " << F1.Q1->Length() << std::endl;
    /* activate batch processing */
    //new_batch->Activate();
    //new_batch->Passivate();

    /*
     * release by the first Order in the queue
     * created batch should be at firt place in the queue by now
     * so the batch should seize the facility right after this release
     */
    assert(F1.in == this);
    DEBUG("O: fronta pred releasem:" << F1.Q1->Length());

    Release(F1);

    assert(F1.in == new_batch);
    DEBUG("O: fronta po releasu:\t" << F1.Q1->Length());

    total_time(Time - income);
}

/*
 * Constructor calls its parent class Process constructor
 * to set highest priority. This ensure Batch
 * will be first at facility queue and will be activated
 * before any Order processes scheduled at the same time.
 */
Batch::Batch(Order *ord): Process(HIGHEST_PRIORITY)
{
    id = all_batch_cntr++;
    //std::cout << "id = " << id << "\tall_batch_cntr = " << all_batch_cntr << std::endl;
    in_facility = ord;
    add_order(ord);
}

void Batch::Behavior(void)
{
    DEBUG("***B:\t\t\t");

    assert(F1.Busy());
    assert(F1.in == this);

    /*
     * seize facility by batch
     */
    //Seize(F1);

    /* no need for high priority from now */
    Priority = DEFAULT_PRIORITY;

    std::cout << "B: batch obsahuje IDs: ";
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       std::cout << (*it)->id << ", ";
    }
    std::cout << std::endl;

    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       DEBUG("B: pokracovani v case\t" << (Time + 1.5));
       Wait(1.5);
    }

    DEBUG("B: opoustim varku\t");

    /*
     * release facility by batch
     * facility is now ready to be seized by first order
     * in its queue to create new batch
     */
    Release(F1);
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
