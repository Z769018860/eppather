int func() {
    char balls[5];
    int i;
    int state;
    int temp;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        balls[i] = i % 3;
    }
    
    state = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (balls[i] < state) {
            break;
        }
        if (balls[i] > state) {
            state = balls[i];
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (balls[i] > balls[j]) {
                temp = balls[i];
                balls[i] = balls[j];
                balls[j] = temp;
            }
        }
    }
    
    state = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (balls[i] < state) {
            break;
        }
        if (balls[i] > state) {
            state = balls[i];
        }
    }
    
    return;
}
