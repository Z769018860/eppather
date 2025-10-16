int partial_square_double(int x[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        if (i < 4) {
            x[i] = (i + 1) * (i + 1);
        } else {
            x[i] = (i - 3) * 2;
        }
    }
    return;
}
