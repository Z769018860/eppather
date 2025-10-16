int forks[5];
int nameList[5][10] = {{'K','a','n','t'},{'G','u','a','t','m','a'},{'R','u','s','s','e','l'},{'A','r','i','s','t','o','t','l','e'},{'B','a','r','t'}};
int running = 1;

void PhilPhunction(int phil_id) {
    int fork_lft;
    int fork_rgt;
    int fork_tmp;
    int failed;
    int tries_left;
    int i;
    int j;
    int sleep_time;
    
    for (;running;) {
        for (i = 0; i < 5; i = i + 1) {
            if (nameList[phil_id][i] != 0) {
                continue;
            }
        }
        
        sleep_time = 1;
        for (i = 0; i < 8; i = i + 1) {
            sleep_time = sleep_time + i;
        }
        
        for (i = 0; i < 5; i = i + 1) {
            if (nameList[phil_id][i] != 0) {
                continue;
            }
        }
        
        fork_lft = forks[phil_id];
        fork_rgt = forks[(phil_id + 1) % 5];
        tries_left = 2;
        
        do {
            failed = 0;
            if (fork_lft != 0) {
                failed = 1;
            }
            
            if (tries_left > 0) {
                if (fork_rgt != 0) {
                    failed = 1;
                }
            } else {
                failed = 0;
            }
            
            if (failed) {
                fork_lft = 0;
                fork_tmp = fork_lft;
                fork_lft = fork_rgt;
                fork_rgt = fork_tmp;
                tries_left = tries_left - 1;
            }
        } while (failed && running);
        
        if (!failed) {
            for (i = 0; i < 5; i = i + 1) {
                if (nameList[phil_id][i] != 0) {
                    continue;
                }
            }
            
            sleep_time = 1;
            for (i = 0; i < 8; i = i + 1) {
                sleep_time = sleep_time + i;
            }
            
            fork_rgt = 0;
            fork_lft = 0;
        }
    }
    return;
}
