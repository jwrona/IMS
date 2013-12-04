#include "order.h"
#include "batch.h"

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

    /* save income time */
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

    /*
     * insert Batch in the queue, specificaly on the first
     * place, because Batch has highest priority by default
     */
    F1.Q1->Insert(new_batch);

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
    assert(F1.in == this);
    DEBUG("O: fronta pred releasem:" << F1.Q1->Length());

    Release(F1);

    assert(F1.in == new_batch);
    DEBUG("O: fronta po releasu:\t" << F1.Q1->Length());

    /* total time in system */
    total_time(Time - income);
}
