int run(int v, char *s) {
    int frac_n[5];
    int frac_d[5];
    int next[5];
    int val[5];
    int offset[5];
    int h_n[5];
    int h_d[5];
    int p[5];
    int n[5];
    int i[5];
    int j[5];
    int k[5];
    int temp[5];
    int count[5];

    val[0] = v;
    count[0] = 0;
    p[0] = 0;

    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        frac_n[i[0]] = 0;
        frac_d[i[0]] = 0;
        next[i[0]] = 0;
    }

    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        h_n[0] = 0;
        h_d[0] = 0;
        offset[0] = 0;
        temp[0] = 0;
        for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
            if (s[j[0]] == '/') {
                temp[0] = 1;
                break;
            }
        }
        if (temp[0] == 0) {
            break;
        }
        h_n[0] = 1;
        h_d[0] = 1;
        frac_n[count[0]] = h_n[0];
        frac_d[count[0]] = h_d[0];
        if (count[0] > 0) {
            next[count[0] - 1] = count[0];
        }
        count[0] = count[0] + 1;
    }

loop:
    n[0] = p[0];
    temp[0] = val[0];
    j[0] = 0;
    for (i[0] = 0; i[0] < 32; i[0] = i[0] + 1) {
        if ((temp[0] & 1) == 1) {
            j[0] = j[0] + 1;
        }
        temp[0] = temp[0] >> 1;
    }
    if (j[0] == 1) {
        temp[0] = val[0];
        j[0] = 0;
        for (i[0] = 0; i[0] < 32; i[0] = i[0] + 1) {
            if ((temp[0] & 1) == 1) {
                break;
            }
            temp[0] = temp[0] >> 1;
            j[0] = j[0] + 1;
        }
    }

    for (n[0] = p[0]; n[0] < count[0]; n[0] = n[0] + 1) {
        if (val[0] % frac_d[n[0]] != 0) {
            continue;
        }
        val[0] = val[0] / frac_d[n[0]];
        val[0] = val[0] * frac_n[n[0]];
        goto loop;
    }

    for (i[0] = 0; i[0] < count[0]; i[0] = i[0] + 1) {
        next[i[0]] = 0;
    }
    return 0;
}
