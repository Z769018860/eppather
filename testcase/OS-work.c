static void work_queue_main(void *workq_ptr, void *p2, void *p3)
{
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    struct k_work_q *queue = (struct k_work_q *)workq_ptr;

    while (true) {
        sys_snode_t *node;
        struct k_work *work = NULL;
        k_work_handler_t handler = NULL;
        k_spinlock_key_t key = k_spin_lock(&lock);
        bool yield;

        /* Check for and prepare any new work. */
        node = sys_slist_get(&queue->pending);
        if (node != NULL) {
            /* Mark that there's some work active that's
             * not on the pending list.
             */
            flag_set(&queue->flags, K_WORK_QUEUE_BUSY_BIT);
            work = CONTAINER_OF(node, struct k_work, node);
            flag_set(&work->flags, K_WORK_RUNNING_BIT);
            flag_clear(&work->flags, K_WORK_QUEUED_BIT);

            /* Static code analysis tool can raise a false-positive violation
             * in the line below that 'work' is checked for null after being
             * dereferenced.
             *
             * The work is figured out by CONTAINER_OF, as a container
             * of type struct k_work that contains the node.
             * The only way for it to be NULL is if node would be a member
             * of struct k_work object that has been placed at address NULL,
             * which should never happen, even line 'if (work != NULL)'
             * ensures that.
             * This means that if node is not NULL, then work will not be NULL.
             */
            handler = work->handler;
        } else if (flag_test_and_clear(&queue->flags,
                           K_WORK_QUEUE_DRAIN_BIT)) {
            /* Not busy and draining: move threads waiting for
             * drain to ready state.  The held spinlock inhibits
             * immediate reschedule; released threads get their
             * chance when this invokes z_sched_wait() below.
             *
             * We don't touch K_WORK_QUEUE_PLUGGABLE, so getting
             * here doesn't mean that the queue will allow new
             * submissions.
             */
            (void)z_sched_wake_all(&queue->drainq, 1, NULL);
        } else if (flag_test(&queue->flags, K_WORK_QUEUE_STOP_BIT)) {
            /* User has requested that the queue stop. Clear the status flags and exit.
             */
            flags_set(&queue->flags, 0);
            k_spin_unlock(&lock, key);
            return;
        } else {
            /* No work is available and no queue state requires
             * special handling.
             */
            ;
        }

        if (work == NULL) {
            /* Nothing's had a chance to add work since we took
             * the lock, and we didn't find work nor got asked to
             * stop.  Just go to sleep: when something happens the
             * work thread will be woken and we can check again.
             */

            (void)z_sched_wait(&lock, key, &queue->notifyq,
                       K_FOREVER, NULL);
            continue;
        }

#if defined(CONFIG_WORKQUEUE_WORK_TIMEOUT)
        work_timeout_start_locked(queue, work);
#endif /* defined(CONFIG_WORKQUEUE_WORK_TIMEOUT) */

        k_spin_unlock(&lock, key);

        __ASSERT_NO_MSG(handler != NULL);
        handler(work);

        /* Mark the work item as no longer running and deal
         * with any cancellation and flushing issued while it
         * was running.  Clear the BUSY flag and optionally
         * yield to prevent starving other threads.
         */
        key = k_spin_lock(&lock);

#if defined(CONFIG_WORKQUEUE_WORK_TIMEOUT)
        work_timeout_stop_locked(queue);
#endif /* defined(CONFIG_WORKQUEUE_WORK_TIMEOUT) */

        flag_clear(&work->flags, K_WORK_RUNNING_BIT);
        if (flag_test(&work->flags, K_WORK_FLUSHING_BIT)) {
            finalize_flush_locked(work);
        }
        if (flag_test(&work->flags, K_WORK_CANCELING_BIT)) {
            finalize_cancel_locked(work);
        }

        flag_clear(&queue->flags, K_WORK_QUEUE_BUSY_BIT);
        yield = !flag_test(&queue->flags, K_WORK_QUEUE_NO_YIELD_BIT);
        k_spin_unlock(&lock, key);

        /* Optionally yield to prevent the work queue from
         * starving other threads.
         */
        if (yield) {
            k_yield();
        }
    }
}