int rand5_7(int rand_max_param, int n1, int n2) {
    int rand5_result[5];
    int r[5];
    int rand_max[5];
    rand_max[0] = rand_max_param - (rand_max_param % 5);
    for (int i = 0; i < 5; i = i + 1) {
        r[0] = 0;
        while (r[0] < rand_max[0]) {
            r[0] = r[0] + 1;
        }
        rand5_result[0] = r[0] / (rand_max[0] / 5) + 1;
    }

    for (int i = 0; i < 5; i = i + 1) {
        r[0] = 0;
        while (r[0] < 27) {
            r[0] = rand5_result[0] * 5 + rand5_result[0];
        }
        r[0] = r[0] / 3 - 1;
    }
    return r[0];
}
