#include "batch.h"
#include "order.h"
#include "main.h"

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

    assert(chef_fac.Busy());
    assert(chef_fac.in == this);

    /* facitily is allready seized by this process */
    //Seize(chef_fac);

    /* no need for high priority from now */
    Priority = DEFAULT_PRIORITY;

#ifndef NDEBUG_PRINT
    //prints IDs of order processes in this batch
    std::cout << "B: zacatek batch obsahuje IDs: ";
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       std::cout << (*it)->get_id() << ", ";
    }
    std::cout << std::endl;
#endif //NDEBUG_PRINT

    /*
     * loop through all orders in batch to simulate
     * pizza preparation
     * duration: 2-3 minutes for every pizza
     */
    std::vector<Order*>::iterator begin = orders.begin();
    std::vector<Order*>::iterator end = orders.end();
    for(std::vector<Order*>::iterator it = begin; it != end; ++it)
    {
        if(std::find(orders.begin(), orders.end(), *it)
           == orders.end())
        {
            /* order no longer in batch because of timer
             * expiration (customer canceled order)
             */
        }
        else
        {
            /* order not canceled yet
             * going to wait (prepare pizza)
             * 2 to 3 minutes for every pizza
             */
            Wait(Uniform(PREP_TIME_FROM, PREP_TIME_TO));

            if(std::find(orders.begin(), orders.end(), *it)
               == orders.end())
            {
                /* order canceled durign waiting (preparation )*/
            }
            else
            {
                /* order was not canceled duritg preparation */
            }
        }
    }

    if (is_empty())
    {
        DEBUG("B: All orders canceled during prepararation, "
        << "releasing chef facility and returning from behavior");
        Release(chef_fac);
        return;
    }

#ifndef NDEBUG_PRINT
    //prints IDs of order processes in this batch
    std::cout << "B: konec batch obsahuje IDs: ";
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       std::cout << (*it)->get_id() << ", ";
    }
    std::cout << std::endl;
#endif //NDEBUG_PRINT

    /*
     * release facility by batch
     * facility is now ready to be seized by first order
     * in its queue to create new batch
     */
    Release(chef_fac);
    DEBUG("B: priprava hotova\t\t");

    /*
     * loop through all orders in batch to
     * create statistics and cancel orders processes
     * (they are all passivated)
     */
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
       DEBUG("O: Proces odchazi prirozene\t");
       (*it)->delete_timeout();
       (*it)->Cancel();
    }
}

void Batch::add_order(Order *ord)
{
    if (is_full())
        Print("Batch is full.\n");
    else if(std::find(orders.begin(), orders.end(), ord) != orders.end())
        Print("Order allready in batch.\n");
    else
    {
        orders.push_back(ord);
	ord->set_batch(this);
    }
}

void Batch::remove_order(Order *ord)
{
    if (is_empty())
        Print("Batch is empty.\n");

    std::vector<Order*>::iterator find_result = std::find(orders.begin(), orders.end(), ord);
    if (find_result == orders.end())
        Print("Order not in batch.\n");
    else
    {
	orders.erase(find_result);
	ord->set_batch(nullptr);
    }
}

bool Batch::is_full(void)
{
    return (orders.size() == BATCH_CAPACITY);
}

bool Batch::is_empty(void)
{
    return (orders.size() == 0);
}
