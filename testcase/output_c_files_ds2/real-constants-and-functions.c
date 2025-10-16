int rewritten_function(int x, int y) {
    int result[5];
    int e = 2;
    int pi = 3;
    result[0] = x;
    result[1] = y;
    result[2] = 0;
    result[3] = 0;
    result[4] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            result[2] = result[0] * result[0];
        }
        if (i == 1) {
            result[3] = result[0] * result[0] * result[0];
        }
        if (i == 2) {
            if (result[0] < 0) {
                result[4] = -result[0];
            } else {
                result[4] = result[0];
            }
        }
        if (i == 3) {
            if (result[1] < 0) {
                result[4] = -result[1];
            } else {
                result[4] = result[1];
            }
        }
        if (i == 4) {
            result[4] = 1;
            for (int j = 0; j < result[1]; j = j + 1) {
                result[4] = result[4] * result[0];
            }
        }
    }
    return;
}
