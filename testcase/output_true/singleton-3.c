int JumpOverTheDog(int n) {
    int x[5];
    x[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (x[0] < n) {
            x[0] = x[0] + 1;
        }
    }
    return;
}

int PlayFetchWithDog(int n) {
    int x[5];
    x[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (x[0] < n) {
            x[0] = x[0] + 1;
        }
    }
    return x[0];
}
