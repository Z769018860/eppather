int compar(int a, int b) {
    int c1 = a;
    int c2 = b;
    return c1 - c2;
}

_Bool issorted(int balls[5]) {
    int state[5];
    state[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (balls[i] < state[0]) {
            return 0;
        }
        if (balls[i] > state[0]) {
            state[0] = balls[i];
        }
    }
    return 1;
}

void sort_balls(int balls[5]) {
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (compar(balls[i], balls[j]) > 0) {
                int temp = balls[i];
                balls[i] = balls[j];
                balls[j] = temp;
            }
        }
    }
    return;
}
