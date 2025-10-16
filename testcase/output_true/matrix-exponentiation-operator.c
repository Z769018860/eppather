void ffMatxSquare(double cells[5], int rw, int dim, int m0_m[5][5], int m0_cells[25]) {
    int col;
    int ix;
    double sum;
    double m0rw[5];
    for (ix = 0; ix < 5; ix = ix + 1) {
        m0rw[ix] = m0_m[rw][ix];
    }
    for (col = 0; col < 5; col = col + 1) {
        sum = 0.0;
        for (ix = 0; ix < 5; ix = ix + 1) {
            sum = sum + m0rw[ix] * m0_m[ix][col];
        }
        cells[col] = sum;
    }
    return;
}

void ffMatxMulply(double cells[5], int rw, int dim, int mleft_m[5][5], int mleft_cells[25], int mrigt_m[5][5], int mrigt_cells[25]) {
    double sum;
    double m0rw[5];
    int col;
    int ix;
    for (ix = 0; ix < 5; ix = ix + 1) {
        m0rw[ix] = mleft_m[rw][ix];
    }
    for (col = 0; col < 5; col = col + 1) {
        sum = 0.0;
        for (ix = 0; ix < 5; ix = ix + 1) {
            sum = sum + m0rw[ix] * mrigt_m[ix][col];
        }
        cells[col] = sum;
    }
    return;
}

void ffIdentity(double cells[5], int rw, int dim, void *v) {
    int col;
    for (col = 0; col < 5; col = col + 1) {
        cells[col] = 0.0;
    }
    cells[rw] = 1.0;
    return;
}

void ffCopy(double cells[5], int rw, int dim, int m1_m[5][5], int m1_cells[25]) {
    int col;
    for (col = 0; col < 5; col = col + 1) {
        cells[col] = m1_m[rw][col];
    }
    return;
}

void fillInit(double cells[5], int rw, int dim, void *data) {
    double theta = 0.5235987756;
    double c1 = 0.8660254038;
    double s1 = 0.5;
    if (rw == 0) {
        cells[0] = c1;
        cells[1] = s1;
        cells[2] = 0.0;
    } else {
        if (rw == 1) {
            cells[0] = -s1;
            cells[1] = c1;
            cells[2] = 0.0;
        } else {
            if (rw == 2) {
                cells[0] = 0.0;
                cells[1] = 0.0;
                cells[2] = 1.0;
            }
        }
    }
    return;
}
