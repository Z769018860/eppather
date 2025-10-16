int func(int inputs[5]) {
    int check[5];
    check[0] = 400;
    int result[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        inputs[i] = 0;
    }
    
    for (i = 4; i >= 0; i = i - 1) {
        int temp[5];
        temp[0] = inputs[i];
        if (temp[0] < 0) {
            temp[0] = -temp[0];
        }
        
        int sqrt_val[5];
        sqrt_val[0] = 1;
        for (int j = 0; j < 5; j = j + 1) {
            if (sqrt_val[0] * sqrt_val[0] <= temp[0]) {
                sqrt_val[0] = sqrt_val[0] + 1;
            } else {
                sqrt_val[0] = sqrt_val[0] - 1;
                break;
            }
        }
        
        int cube[5];
        cube[0] = inputs[i] * inputs[i] * inputs[i];
        result[0] = sqrt_val[0] + 5 * cube[0];
        
        if (result[0] > check[0]) {
            result[0] = -1;
        } else {
            result[0] = result[0];
        }
    }
    
    return;
}
