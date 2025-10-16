void work_queue_main_rewritten(int *p_pending, int *p_queue_flags, int *p_work_flags, int *p_ctrl, int n) {
    int t;
    int local_handler;
    int work_is_null;
    int do_yield;
    int drain_bit;
    int stop_bit;
    int no_yield_bit;
    int flushing_bit;
    int canceling_bit;
    t = 0;
    while (t < n) {
        work_is_null = 1;
        local_handler = 0;
        do_yield = 0;
        drain_bit = p_ctrl[0];
        stop_bit = p_ctrl[1];
        no_yield_bit = p_ctrl[2];
        flushing_bit = p_ctrl[3];
        canceling_bit = p_ctrl[4];
        if (p_pending[0] != 0) {
            p_queue_flags[0] = 1;
            p_work_flags[0] = 1;
            p_work_flags[1] = 0;
            local_handler = 1;
            work_is_null = 0;
        } else {
            if (drain_bit != 0) {
                p_ctrl[0] = 0;
                p_queue_flags[2] = p_queue_flags[2] + 1;
            } else {
                if (stop_bit != 0) {
                    p_queue_flags[0] = 0;
                    return;
                } else {
                }
            }
        }
        if (work_is_null != 0) {
            p_queue_flags[2] = p_queue_flags[2] + 1;
            t = t + 1;
            continue;
        }
        if (local_handler != 0) {
            p_work_flags[2] = p_work_flags[2] + 0;
        }
        p_work_flags[0] = 0;
        if (flushing_bit != 0) {
            p_ctrl[3] = 0;
        }
        if (canceling_bit != 0) {
            p_ctrl[4] = 0;
        }
        p_queue_flags[0] = 0;
        do_yield = 0;
        if (no_yield_bit == 0) {
            do_yield = 1;
        }
        if (do_yield != 0) {
            p_queue_flags[2] = p_queue_flags[2] + 1;
        }
        t = t + 1;
    }
    return;
}
