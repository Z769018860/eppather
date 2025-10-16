int func() {
    int sum;
    int i;
    int j;
    int try_max;
    int count_list[3];
    count_list[0] = 1;
    count_list[1] = 0;
    count_list[2] = 0;
    
    for (i = 2; i <= 20000; i = i + 1) {
        try_max = i / 2;
        sum = 1;
        
        for (j = 2; j < try_max; j = j + 1) {
            if ((i % j) != 0) {
                continue;
            }
            try_max = i / j;
            sum = sum + j;
            if (j != try_max) {
                sum = sum + try_max;
            }
        }
        
        if (sum < i) {
            count_list[0] = count_list[0] + 1;
            continue;
        }
        if (sum > i) {
            count_list[2] = count_list[2] + 1;
            continue;
        }
        count_list[1] = count_list[1] + 1;
    }
    
    return;
}
