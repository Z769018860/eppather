void merged_thread_func(int bang[5], int condm[5], int cond[5]) {
    if (bang[0] == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            if (condm[0] != 0) {
                cond[0] = 1;
            }
        }
    }
    if (bang[0] == 1) {
        for (int i = 0; i < 5; i = i + 1) {
            if (condm[0] != 0) {
                cond[0] = 0;
            }
        }
    }
    return;
}
