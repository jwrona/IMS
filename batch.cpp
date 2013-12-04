#include "batch.h"
#include "order.h"

/*
 * Constructor calls its parent class Process constructor
 * to set highest priority. This ensure Batch will be first
 * at facitily queue.
 */
Batch::Batch(Order *ord): Process(HIGHEST_PRIORITY)
{
    id = all_batch_cntr++;
    in_facility = ord;
    add_order(ord);
}

void Batch::Behavior(void)
{
    DEBUG("***B:\t\t\t");

    assert(F1.Busy());
    assert(F1.in == this);

    /* facitily is allready seized by this process */
    //Seize(F1);

    /* no need for high priority from now */
    Priority = DEFAULT_PRIORITY;

    #ifndef NDEBUG_PRINT
    //prints IDs of order processes in this batch
    std::cout << "B: batch obsahuje IDs: ";
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       std::cout << (*it)->id << ", ";
    }
    std::cout << std::endl;
    #endif //NDEBUG_PRINT

    /*
     * loop through all orders in batch
     */
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
        Print("Order allready in batch.\n");
    else
        orders.push_back(ord);
}

bool Batch::is_full(void)
{
    return (orders.size() == batch_capacity);
}