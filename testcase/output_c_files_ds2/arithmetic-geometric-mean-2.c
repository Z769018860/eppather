void agm(int in1[5], int in2[5], int out1[5], int out2[5]) {
    for (int i = 0; i < 5; i = i + 1) {
        out1[i] = in1[i] + in2[i];
    }
    for (int i = 0; i < 5; i = i + 1) {
        out1[i] = out1[i] / 2;
    }
    for (int i = 0; i < 5; i = i + 1) {
        out2[i] = in1[i] * in2[i];
    }
    for (int i = 0; i < 5; i = i + 1) {
        int j = 0;
        while (j * j <= out2[i]) {
            j = j + 1;
        }
        out2[i] = j - 1;
    }
    return;
}
