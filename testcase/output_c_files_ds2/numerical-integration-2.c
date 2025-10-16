int integration(int x[5], int y[5], int z[5], int w[5], int func_type) {
    int result[5];
    int i;
    int j;
    int k;
    int n;
    int m;
    
    for (i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    
    if (func_type == 0) {
        for (i = 0; i < 5; i = i + 1) {
            result[0] = x[0];
        }
    } else if (func_type == 1) {
        for (i = 0; i < 5; i = i + 1) {
            result[0] = (x[0] * x[0]) / 2;
        }
    } else if (func_type == 2) {
        for (i = 0; i < 5; i = i + 1) {
            if (x[0] != 0) {
                result[0] = 1 / x[0];
            }
        }
    } else if (func_type == 3) {
        for (i = 0; i < 5; i = i + 1) {
            result[0] = x[0];
        }
    } else if (func_type == 4) {
        for (i = 0; i < 5; i = i + 1) {
            result[0] = x[0] * x[0] * x[0];
        }
    } else if (func_type == 5) {
        for (i = 0; i < 5; i = i + 1) {
            result[0] = (x[0] * x[0] * x[0] * x[0]) / 4;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        y[0] = result[0] - x[0];
    }
    
    return;
}
