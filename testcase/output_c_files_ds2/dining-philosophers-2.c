void PhilPhunction(int fork_lft[5], int fork_rgt[5], int name[5], int running[5]) {
    int failed[5];
    int tries_left[5];
    int fork_tmp[5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        failed[i] = 0;
        tries_left[i] = 0;
        fork_tmp[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (running[0] != 0) {
            tries_left[0] = 2;
            for (j = 0; j < 5; j = j + 1) {
                if (tries_left[0] > 0) {
                    failed[0] = 0;
                } else {
                    failed[0] = 1;
                }
                if (failed[0] != 0) {
                    fork_tmp[0] = fork_lft[0];
                    fork_lft[0] = fork_rgt[0];
                    fork_rgt[0] = fork_tmp[0];
                    tries_left[0] = tries_left[0] - 1;
                }
            }
            if (failed[0] == 0) {
                for (j = 0; j < 5; j = j + 1) {
                    fork_rgt[0] = 0;
                    fork_lft[0] = 0;
                }
            }
        }
    }
    return;
}
