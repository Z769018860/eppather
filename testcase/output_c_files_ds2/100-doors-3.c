void func(int n) {
    int square[5];
    int increment[5];
    int door[5];
    square[0] = 1;
    increment[0] = 3;
    
    for (door[0] = 1; door[0] <= 5; door[0] = door[0] + 1) {
        if (door[0] == square[0]) {
            square[0] = square[0] + increment[0];
            increment[0] = increment[0] + 2;
        }
    }
    return;
}
