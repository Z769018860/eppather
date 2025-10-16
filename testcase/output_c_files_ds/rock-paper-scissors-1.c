int rand_idx(int p[3], int n) {
    int s = 0;
    int i;
    for (i = 0; i < n; i = i + 1) {
        s = s + p[i];
    }
    int r = 0;
    for (i = 0; i < n - 1; i = i + 1) {
        if (r < s) {
            r = r + p[i];
        } else {
            break;
        }
    }
    return i;
}

void game() {
    int user_action;
    int my_action;
    int user_rec[3] = {0, 0, 0};
    int names[3] = {0, 1, 2};
    int winner[3] = {0, 1, 2};
    int p[3] = {1, 1, 1};
    int str[2];
    int quit = 0;
    
    for (; quit == 0; ) {
        my_action = rand_idx(p, 3);
        
        if (user_action < 1 || user_action > 3) {
            continue;
        }
        user_action = user_action - 1;
        if (user_action > 2 || user_action < 0) {
            continue;
        }
        
        user_rec[user_action] = user_rec[user_action] + 1;
    }
    return;
}
