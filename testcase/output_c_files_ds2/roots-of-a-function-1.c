int f(int x[5]) {
    x[0] = x[0] * x[0] * x[0] - 3 * x[0] * x[0] + 2 * x[0];
    return;
}

int secant(int xA[5], int xB[5], int limit) {
    int e[5] = {0};
    int fA[5] = {0};
    int fB[5] = {0};
    int d[5] = {0};
    int i;
    int temp1[5] = {0};
    int temp2[5] = {0};
    int temp3[5] = {0};
    
    e[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        temp1[0] = xA[0];
        f(temp1);
        fA[0] = temp1[0];
        temp2[0] = xB[0];
        f(temp2);
        fB[0] = temp2[0];
        temp3[0] = xB[0] - xA[0];
        d[0] = temp3[0] / (fB[0] - fA[0]) * fB[0];
        if (d[0] < 0) {
            d[0] = -d[0];
        }
        if (d[0] < e[0]) {
            break;
        }
        xA[0] = xB[0];
        fA[0] = fB[0];
        xB[0] = xB[0] - d[0];
    }
    if (i == 5) {
        return -99;
    }
    return xB[0];
}

int main() {
    int step[5] = {1};
    int e[5] = {1};
    int x[5] = {-1};
    int xx[5] = {0};
    int value[5] = {0};
    int s[5] = {0};
    int temp4[5] = {0};
    int temp5[5] = {0};
    
    temp4[0] = x[0];
    f(temp4);
    if (temp4[0] > 0) {
        s[0] = 1;
    } else {
        s[0] = 0;
    }
    for (x[0] = -1; x[0] < 3; x[0] = x[0] + step[0]) {
        temp5[0] = x[0];
        f(temp5);
        value[0] = temp5[0];
        if (value[0] < 0) {
            value[0] = -value[0];
        }
        if (value[0] < e[0]) {
            s[0] = (f(temp5) > 0);
        } else {
            if ((value[0] > 0) != s[0]) {
                xx[0] = secant(x, x, 5);
                if (xx[0] != -99) {
                    s[0] = (f(temp5) > 0);
                } else {
                    s[0] = (f(temp5) > 0);
                }
            }
        }
    }
    return;
}
