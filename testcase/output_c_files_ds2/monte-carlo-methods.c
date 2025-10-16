int pi(int tolerance) {
    int x[5];
    int y[5];
    int val[5];
    int error[5];
    int sampled[5];
    int hit[5];
    int i;
    int j;

    sampled[0] = 0;
    hit[0] = 0;

    for (j = 0; j < 5; j = j + 1) {
        for (i = 0; i < 5; i = i + 1) {
            x[0] = 0;
            y[0] = 0;
            sampled[0] = sampled[0] + 1;
            if (x[0] * x[0] + y[0] * y[0] < 1) {
                hit[0] = hit[0] + 1;
            }
        }

        val[0] = hit[0] / sampled[0];
        error[0] = 0;
        val[0] = val[0] * 4;

        if (hit[0] == 0 || error[0] > tolerance) {
            continue;
        } else {
            break;
        }
    }

    return val[0];
}
