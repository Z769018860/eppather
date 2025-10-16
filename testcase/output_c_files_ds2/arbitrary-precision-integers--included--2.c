void compute_power(int n1, int n2, int n3, int n4, int n5, int result[5]) {
    int two[5] = {0};
    int three[5] = {0};
    int four[5] = {0};
    int five[5] = {0};
    int answer[5] = {0};
    int context[5] = {0};
    int length[5] = {0};
    int string[5] = {0};

    two[0] = 2;
    three[0] = 3;
    four[0] = 4;
    five[0] = 5;

    answer[0] = three[0];
    for (int i = 0; i < 5; i = i + 1) {
        answer[0] = answer[0] * answer[0];
    }

    answer[0] = four[0];
    for (int i = 0; i < 5; i = i + 1) {
        answer[0] = answer[0] * answer[0];
    }

    answer[0] = five[0];
    for (int i = 0; i < 5; i = i + 1) {
        answer[0] = answer[0] * answer[0];
    }

    result[0] = answer[0];
    return;
}
