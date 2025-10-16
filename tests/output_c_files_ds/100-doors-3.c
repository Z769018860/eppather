int func() {
    int square;
    int increment;
    int door;
    int result[100];
    square = 1;
    increment = 3;
    for (door = 1; door <= 100; door = door + 1) {
        if (door == square) {
            result[door - 1] = 1;
            square = square + increment;
            increment = increment + 2;
        } else {
            result[door - 1] = 0;
        }
    }
    return;
}
