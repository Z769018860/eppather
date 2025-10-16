int func(int k) {
    int result;
    int k_copy = k;
    int x1 = 1;
    int x2 = -1;
    int x3 = -1;
    int x4 = 1;
    int x5 = 0;
    
    for (;;) {
        if (k_copy <= 0) {
            result = x4 + x5;
            break;
        } else {
            k_copy = k_copy - 1;
            int temp_k = k_copy;
            int temp_x1 = x1;
            int temp_x2 = x2;
            int temp_x3 = x3;
            int temp_x4 = x4;
            int temp_x5 = x5;
            
            for (;;) {
                if (temp_k <= 0) {
                    result = temp_x4 + temp_x5;
                    break;
                } else {
                    temp_k = temp_k - 1;
                    x1 = temp_x1;
                    x2 = temp_x2;
                    x3 = temp_x3;
                    x4 = temp_x4;
                    x5 = temp_x5;
                    continue;
                }
            }
        }
    }
    return result;
}
