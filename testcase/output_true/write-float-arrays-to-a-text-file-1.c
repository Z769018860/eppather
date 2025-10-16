void func(int n) {
    int x[5] = {1, 2, 3, 100000000000, 0};
    int y[5] = {0, 0, 0, 0, 0};
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < n) {
            if (x[i] == 1) {
                y[i] = 1;
            } else {
                if (x[i] == 2) {
                    y[i] = 1;
                } else {
                    if (x[i] == 3) {
                        y[i] = 1;
                    } else {
                        if (x[i] == 100000000000) {
                            y[i] = 316227;
                        }
                    }
                }
            }
        }
    }
    return;
}
