int func() {
    int jobs = 41;
    int tid = 0;
    int thread_count = 5;
    int barrier_counter = 0;
    int thread_done[5] = {0, 0, 0, 0, 0};
    int job_taken = 0;

    for (tid = 0; tid < thread_count; tid = tid + 1) {
        for (;;) {
            if (jobs > 0) {
                barrier_counter = barrier_counter + 1;
                if (barrier_counter == thread_count) {
                    barrier_counter = 0;
                }
                if (jobs > 0) {
                    job_taken = jobs;
                    jobs = jobs - 1;
                }
                if (job_taken > 0) {
                    int sleep_time = 100000 + (job_taken * 1000) % 3000000;
                }
            }
            if (jobs <= 0) {
                thread_done[tid] = 1;
                break;
            }
        }

        barrier_counter = barrier_counter + 1;
        if (barrier_counter == thread_count) {
            barrier_counter = 0;
        }
    }

    return;
}
