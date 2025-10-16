int eat(int name, int left, int right, int forks[5]) {
    int locked_left;
    int locked_right;
    locked_left = 0;
    locked_right = 0;
    for (int i = 0; i < 1; i = i + 1) {
        if (forks[left] == 0) {
            forks[left] = 1;
            locked_left = 1;
        }
    }
    for (int i = 0; i < 1; i = i + 1) {
        if (forks[right] == 0) {
            forks[right] = 1;
            locked_right = 1;
        }
    }
    for (int i = 0; i < 1; i = i + 1) {
        if (locked_left == 1 && locked_right == 1) {
            for (int j = 0; j < 100; j = j + 1) {
                int dummy = 0;
            }
        }
    }
    for (int i = 0; i < 1; i = i + 1) {
        if (locked_left == 1) {
            forks[left] = 0;
        }
    }
    for (int i = 0; i < 1; i = i + 1) {
        if (locked_right == 1) {
            forks[right] = 0;
        }
    }
    return;
}
