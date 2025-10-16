int func(int n1, int n2, int n3) {
    int door[5];
    int square[5];
    int increment[5];
    door[0] = 1;
    square[0] = 1;
    increment[0] = 1;
    for (door[0] = 1; door[0] <= 100; door[0] = door[0] + 1) {
        if (door[0] == square[0]) {
            square[0] = square[0] + increment[0];
            increment[0] = increment[0] + 2;
        }
    }
    return;
}
