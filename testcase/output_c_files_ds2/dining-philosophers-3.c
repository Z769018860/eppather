int eat(int name[5], int left, int right, int forks[5]) {
    int time1[5];
    time1[0] = 1;
    {
        int i;
        for (i = 0; i < 5; i = i + 1) {
            if (i == left) {
                forks[i] = 1;
            }
        }
    }
    {
        int i;
        for (i = 0; i < 5; i = i + 1) {
            if (i == right) {
                forks[i] = 1;
            }
        }
    }
    {
        int i;
        for (i = 0; i < 5; i = i + 1) {
            if (i == left) {
                forks[i] = 0;
            }
        }
    }
    {
        int i;
        for (i = 0; i < 5; i = i + 1) {
            if (i == right) {
                forks[i] = 0;
            }
        }
    }
    return;
}
