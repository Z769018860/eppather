void func(int* count_list) {
    int sum[5] = {0};
    int i;
    int j;
    int try_max[5] = {0};
    int n = 20000;
    int n1 = 2;
    int n2 = 1;
    int n3 = 0;
    
    count_list[0] = 1;
    count_list[1] = 0;
    count_list[2] = 0;
    
    for (i = 2; i <= n; i = i + 1) {
        try_max[0] = i / n1;
        sum[0] = n2;
        for (j = n1; j < try_max[0]; j = j + 1) {
            if ((i % j) != 0) {
                continue;
            }
            try_max[0] = i / j;
            sum[0] = sum[0] + j;
            if (j != try_max[0]) {
                sum[0] = sum[0] + try_max[0];
            }
        }
        if (sum[0] < i) {
            count_list[0] = count_list[0] + 1;
            continue;
        }
        if (sum[0] > i) {
            count_list[2] = count_list[2] + 1;
            continue;
        }
        count_list[1] = count_list[1] + 1;
    }
    return;
}
