int binary_search(int bounds[2], char input[2]) {
    int choice;
    choice = (bounds[0] + bounds[1]) / 2;
    for (;;) {
        if (input[0] == 'H') {
            bounds[1] = choice;
        }
        if (input[0] == 'L') {
            bounds[0] = choice;
        }
        if (input[0] == 'Y') {
            return 0;
        }
        choice = (bounds[0] + bounds[1]) / 2;
        return 1;
    }
    return 0;
}
