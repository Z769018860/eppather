int func(int bounds_0, int bounds_1, int input_0, int input_1) {
    int bounds[2];
    bounds[0] = bounds_0;
    bounds[1] = bounds_1;
    int input[2];
    input[0] = input_0;
    input[1] = input_1;
    int choice[5];
    choice[0] = (bounds[0] + bounds[1]) / 2;

    for (int i = 0; i < 5; i = i + 1) {
        if (input[0] == 72) {
            bounds[1] = choice[0];
        } else {
            if (input[0] == 76) {
                bounds[0] = choice[0];
            } else {
                if (input[0] == 89) {
                    return 0;
                }
            }
        }
        choice[0] = (bounds[0] + bounds[1]) / 2;
    }
    return 0;
}
