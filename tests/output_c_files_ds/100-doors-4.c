int func() {
    int door;
    int square;
    int increment;
    int result[100];
    for (door = 1, square = 1, increment = 1; door <= 100; door = door + 1) {
        if (door == square) {
            result[door - 1] = 1;
            square = square + increment + 2;
            increment = increment + 2;
        } else {
            result[door - 1] = 0;
        }
    }
    return;
}
