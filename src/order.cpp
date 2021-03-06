#include "order.h"
#include "main.h"
#include "batch.h"
#include "timeout.h"

Order::Order(bool reparation)
{
    assert((BUSINNESS_LEVEL+ BOWLING_LEVEL + OTHERS_LEVEL) == 100.0);

    /* order id for debug */
    id = all_order_cntr++;

    /* all orders in system now counter */
    /* cannot be used, is not decremented anywhere
    if (++orders_in_system_now >= MAX_ORDERS_IN_SYSTEM)
        refuse_orders = true;
    */

    batch_im_in = nullptr;
    double timeout_length = MAX_TIMEOUT_LENGTH
                            - Exponential(1.0 / TIMEOUT_EXP_SLOPE);
    t = new Timeout(this, timeout_length);

    if (reparation)
    {
        /* reparations have priority over everything */
        Priority = REPARATION;
    }
    else
    {
	/* order priority assignment in at the specified ratio */
	double rnd = Uniform(0.0, 100.0); // 0 - 100 %

	if (rnd <= BUSINNESS_LEVEL)
	    Priority = BUSINESS;
	else if (rnd <= (BUSINNESS_LEVEL + BOWLING_LEVEL))
	    Priority = BOWLING;
	else
	    Priority = OTHERS;
    }
}

Order::~Order(void)
{
    /* cancel timeout if its not null pointer and
     * it doesn't run right now (process made it to the end)
     */
    if ((t != nullptr) && (!t->Idle()))
    {
	t->Cancel();
	t = nullptr;
    }
}


void Order::Behavior(void)
{
    //DEBUG("***O:\t\t\t");

    /* save income time */
    income = Time;

    /* seize by the first Order in the queue */
    Seize(chef_fac);

    /*
     * create batch
     * push order which is occupying facility to the batch
     */
    Batch *new_batch = new Batch(static_cast<Order*>(chef_fac.in));

    /*
     * fill batch with orders
     * pop from the top of the facility queue, push into batch
     */
    //DEBUG("O: fronta pred pushem:\t" << chef_fac.Q1->Length());
    while (!chef_fac.Q1->Empty() && !new_batch->is_full())
	new_batch->add_order(static_cast<Order*>(chef_fac.Q1->GetFirst()));

    //DEBUG("O: fronta po pushi:\t" << chef_fac.Q1->Length());

    /*
     * insert Batch in the queue, specificaly on the first
     * place, because Batch has highest priority by default
     */
    chef_fac.Q1->Insert(new_batch);

    /*
     * no need to activate batch process
     * it allready is in queue, after Release() by this instance,
     * new_batch will seize it and activate itselfs afterwards
     */
    //new_batch->Activate();

    /*
     * releasing the faciliti will cause its seize by Batch
     * because it is first in the queue
     */
    assert(chef_fac.in == this);
    //DEBUG("O: fronta pred releasem:" << chef_fac.Q1->Length());

    Release(chef_fac);

    assert(chef_fac.in == new_batch);
    //DEBUG("O: fronta po releasu:\t" << chef_fac.Q1->Length());

    /*
     * Passivate for the first process who created the batch.
     * Other processes are stucked before Seize() and cannot
     * be Activated, so they all have to be Canceled in Batch.
     */
    Passivate();
}

void Order::repare(void)
{
    Priority = REPARATION;
    chef_fac.Q1->Insert(this); //causes SIGSEV, WHY?
    std::cout << "inserted" << std::endl;
}
