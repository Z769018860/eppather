void parallel_jobs(int jobs) {
    int tid[5];
    int jobs_arr[5];
    jobs_arr[0] = jobs;
    
    for (int i = 0; i < 5; i = i + 1) {
        tid[i] = i;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (; jobs_arr[0] > 0; ) {
            if (jobs_arr[0] == 0) {
                break;
            }
            
            jobs_arr[0] = jobs_arr[0] - 1;
            
            for (int j = 0; j < 5; j = j + 1) {
                if (j == i) {
                    continue;
                }
            }
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (j == i) {
                continue;
            }
        }
    }
    
    return;
}
