void thread_func(int id) {
    int bang_local = 0;
    int condm_locked = 0;
    
    for (condm_locked = 1; condm_locked == 1; condm_locked = condm_locked) {
        if (bang_local == 0) {
            continue;
        }
        condm_locked = 0;
    }
    
    if (id == 0) {
        int output[5] = {'E', 'n', 'j', 'o', 'y'};
    } else if (id == 1) {
        int output[7] = {'R', 'o', 's', 'e', 't', 't', 'a'};
    } else if (id == 2) {
        int output[4] = {'C', 'o', 'd', 'e'};
    }
    
    return;
}
