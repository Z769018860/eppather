int func(int argc, int argv[][100]) {
    int i;
    int j;
    int lval;
    int is_number;
    int is_empty;
    int ep_empty;
    int arg_empty;
    int gt_10;
    int gt_100;
    
    for (i = 1; i < argc; i = i + 1) {
        is_empty = 1;
        for (j = 0; j < 100; j = j + 1) {
            if (argv[i][j] == 0) {
                break;
            }
            is_empty = 0;
        }
        
        lval = 0;
        is_number = 1;
        ep_empty = 1;
        for (j = 0; j < 100; j = j + 1) {
            if (argv[i][j] == 0) {
                break;
            }
            if (argv[i][j] < '0' || argv[i][j] > '9') {
                is_number = 0;
                break;
            }
            lval = lval * 10 + (argv[i][j] - '0');
            ep_empty = 0;
        }
        
        arg_empty = is_empty;
        if (arg_empty) {
            continue;
        }
        
        if (is_number) {
            gt_10 = lval > 10;
            gt_100 = lval > 100;
            if (gt_10) {
                if (gt_100) {
                    continue;
                } else {
                    continue;
                }
            } else {
                if (gt_100) {
                    continue;
                } else {
                    continue;
                }
            }
        } else {
            continue;
        }
    }
    return;
}
