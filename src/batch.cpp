#include "batch.h"
#include "main.h"
#include "order.h"
#include "timeout.h"

/*
 * Constructor calls its parent class Process constructor
 * to set highest priority. This ensure Batch will be first
 * at chef_fac queue.
 */
Batch::Batch(Order *ord): Process(HIGHEST_PRIORITY)
{
    id = all_batch_cntr++;
    add_order(ord);
}

void Batch::Behavior(void)
{
    std::vector<Order*>::iterator begin;
    std::vector<Order*>::iterator end;
    DEBUG("NEW BATCH:\t\t");

    assert(chef_fac.Busy());
    assert(chef_fac.in == this);

    /* facitily is allready seized by this process */
    //Seize(chef_fac);

    /* no need for high priority from now */
    Priority = DEFAULT_PRIORITY;

#ifndef NDEBUG_PRINT
    //prints IDs of order processes in this batch
    std::cout << "\tIDs: ";
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
        if ((*it)->get_batch() == nullptr)
           std::cout << (*it)->get_id() << "(D), ";
        else
           std::cout << (*it)->get_id() << ", ";
    }
    std::cout << std::endl;
#endif //NDEBUG_PRINT

    ////////////////////////////////////////////////////////////
    //preparation
    ////////////////////////////////////////////////////////////

    DEBUG("PREPARATION\t\t");
    /*
     * loop through all orders in batch to simulate
     * pizza preparation
     * duration: 2-3 minutes for each pizza
     */
    begin = orders.begin();
    end = orders.end();
    for(std::vector<Order*>::iterator it = begin; it != end; ++it)
    {  //for every pizza in batch
        if ((*it)->get_batch() == nullptr)
        {
            /* order no longer in batch because of timer
             * expiration (customer canceled order)
             */
        }
        else
        {
            /* order not canceled yet
             * going to wait (prepare pizza)
             * 4 to 5 minutes for every pizza
             */
            Wait(Uniform(PREP_TIME_FROM, PREP_TIME_TO));

            if ((*it)->get_batch() == nullptr)
            {
                /* order canceled durign waiting (preparation )*/
            }
            else
            {
                /* order was not canceled duritg preparation */
            }
        }
    }

    /*
     * release chef facility by batch
     * facility is now ready to be seized by first order
     * in its queue to create new batch
     */
    Release(chef_fac);
    DEBUG("PREPARATION DONE\t");


    /*
     * loop through all orders in batch to simulate
     * pizza preparation error rate
     */
    begin = orders.begin();
    end = orders.end();
    for(std::vector<Order*>::iterator it = begin; it != end; ++it)
    {  //for every pizza in batch
        if ((*it)->get_batch() != nullptr)
        {
            double rnd = Uniform(0.0, 100.0); // 0 - 100 %
            if (rnd <= PREP_ERR_RATE)
            {
                DEBUG("PREPARATION ERROR\t");
                /* there was an error, pizza have to be removed
                 * from batch, order will be canceled 
                 * (no reparation for now)
                 */
                assert((*it)->get_batch() == this);
                remove_order(*it);
            }
        }
    }

#ifndef NDEBUG
    begin = orders.begin();
    end = orders.end();
    for(std::vector<Order*>::iterator it = begin; it != end; ++it)
        assert((*it)->get_batch() == this || (*it)->get_batch() == nullptr);
#endif //NDEBUG

    ////////////////////////////////////////////////////////////
    //baking
    ////////////////////////////////////////////////////////////

    /* if batch is not empty, simulate pizza baking
     * duration: exactly 4 minutes for batch
     */
    if (!is_empty())
    {
        Seize(oven_fac);
        DEBUG("BAKING\t\t\t");
        Wait(BAKING_TIME);
        Release(oven_fac);
        DEBUG("BAKING DONE\t\t");

        /* simulate error in baking */
        double rnd = Uniform(0.0, 100.0); // 0 - 100 %
        if (rnd <= BAKING_ERR_RATE)
        {
            DEBUG("BAKING ERROR\t\t");
            /* there was an error in baking, batch and all its
             * orders will be canceled
             * (no reparation for now)
             */
            begin = orders.begin();
            end = orders.end();
            for(std::vector<Order*>::iterator it = begin;
                it != end; ++it)
            {  //for every pizza in batch
                if ((*it)->get_batch() != nullptr)
                {
                    assert((*it)->get_batch() == this);
                    remove_order(*it);
                }
            }
            assert(this->is_empty());
        }
    }

    ////////////////////////////////////////////////////////////
    //delivery
    ////////////////////////////////////////////////////////////

    /* if batch is not empty, simulate pizza delivery
     * duration: exactly 10 - 15 minutes for each pizza
     */
    if (!is_empty())
    {
        Enter(delivery_store);
        DEBUG("DELIVERY\t\t");

        begin = orders.begin();
        end = orders.end();
        for(std::vector<Order*>::iterator it = begin;
            it != end; ++it)
        {  //for every pizza in batch
            if ((*it)->get_batch() == nullptr)
            {
                /* order no longer in batch because of timer
                 * expiration (customer canceled order)
                 */
            }
            else
            {
                /* order not canceled yet */
                Wait(Uniform(DELIV_TIME_FROM, DELIV_TIME_TO));

                if ((*it)->get_batch() == nullptr)
                {
                    /* order canceled durign delivery */
                }
                else
                {
                    /* order was not canceled during delivery */
                }
            }
        }

        Leave(delivery_store);
        DEBUG("DELIVERY DONE\t\t");
    }

    ////////////////////////////////////////////////////////////
    //finishing process
    ////////////////////////////////////////////////////////////

    /*
     * loop through all orders in batch to
     * create statistics
     * (they are all passivated)
     */
    DEBUG("FINISHED BATCH:\t\t");
    //std::cout << "\tIDs: ";
    begin = orders.begin();
    end = orders.end();
    for(std::vector<Order*>::iterator it = begin; it != end; ++it)
    {  //for every pizza in batch
        if ((*it)->get_batch() == nullptr)
        { //deleted
           //std::cout << (*it)->get_id() << "(D), ";
           /*
            * timeout is allready canceled
            */
        }
        else
        { //finished
           //std::cout << (*it)->get_id() << ", ";

           /* cancel timeout, process succesfully finished */
           if ((*it)->t != nullptr)
               (*it)->t->Cancel();

           (*it)->t = nullptr;
        }
    }
    //std::cout << std::endl;
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
        /* cancel timeout (if its not running right now)
         * process didn't finish successfully
         */
        if ((ord->t != nullptr) && (!ord->t->Idle()))
        {
            ord->t->Cancel();
            ord->t = nullptr;
        }

        //removed_orders.push_back(*find_result);
	//orders.erase(find_result);
	ord->set_batch(nullptr);
    }
}

bool Batch::is_full(void)
{
    return (orders.size() == BATCH_CAPACITY);
}

bool Batch::is_empty(void)
{
    for(std::vector<Order*>::iterator it = orders.begin();
        it != orders.end(); ++it)
    {
        if ((*it)->get_batch() != nullptr)
           return false;
    }
    return true;
}
