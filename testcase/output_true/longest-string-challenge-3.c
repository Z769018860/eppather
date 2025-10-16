int func(int x, int y, int a[5], int b[5]) {
    int x_arr[5] = {0};
    int y_arr[5] = {0};
    int result[5] = {0};
    int tmp[5] = {0};
    int i = 0;
    
    x_arr[0] = x;
    y_arr[0] = y;
    
    for (i = 0; i < 5; i = i + 1) {
        tmp[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (y_arr[0] && x_arr[0]) {
            y_arr[0] = y_arr[0] - 1;
            x_arr[0] = x_arr[0] - 1;
        }
    }
    result[0] = x_arr[0];
    
    if (!result[0]) {
        for (i = 0; i < 5; i = i + 1) {
            if (y_arr[0] && x_arr[0]) {
                y_arr[0] = y_arr[0] - 1;
                x_arr[0] = x_arr[0] - 1;
            }
        }
        tmp[0] = y_arr[0];
        if (!tmp[0]) {
            result[0] = 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (y_arr[0]) {
            x_arr[0] = x_arr[0] + 1;
            y_arr[0] = y_arr[0] - 1;
        }
    }
    result[0] = x_arr[0];
    
    for (i = 0; i < 5; i = i + 1) {
        if (a[i]) {
            tmp[0] = tmp[0] + 1;
        }
    }
    result[0] = tmp[0];
    
    return;
}
