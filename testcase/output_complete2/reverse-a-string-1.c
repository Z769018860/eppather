int is_comb(int c[5]) {
    if (c[0] >= 768 && c[0] <= 879) { return 1; }
    if (c[0] >= 7616 && c[0] <= 7679) { return 1; }
    if (c[0] >= 8400 && c[0] <= 8447) { return 1; }
    if (c[0] >= 65056 && c[0] <= 65071) { return 1; }
    return 0;
}

void mb_to_wchar(int s[5], int u[5]) {
    int len[5];
    len[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (s[i] == 0) { break; }
        len[0] = len[0] + 1;
    }
    len[0] = len[0] + 1;
    for (int i = 0; i < len[0]; i = i + 1) {
        u[i] = s[i];
    }
    return;
}

void ws_reverse(int u[5], int out[5]) {
    int len[5];
    int i[5];
    int j[5];
    len[0] = 0;
    for (int k = 0; k < 5; k = k + 1) {
        if (u[k] == 0) { break; }
        len[0] = len[0] + 1;
    }
    out[len[0]] = 0;
    j[0] = 0;
    while (len[0] > 0) {
        i[0] = len[0] - 1;
        while (i[0] > 0 && is_comb(&u[i[0]])) {
            i[0] = i[0] - 1;
        }
        for (int k = i[0]; k < len[0]; k = k + 1) {
            out[j[0] + k - i[0]] = u[k];
        }
        j[0] = j[0] + len[0] - i[0];
        len[0] = i[0];
    }
    return;
}

void mb_reverse(int in[5], int out[5]) {
    int u[5];
    int r[5];
    mb_to_wchar(in, u);
    ws_reverse(u, r);
    int len[5];
    len[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (r[i] == 0) { break; }
        len[0] = len[0] + 1;
    }
    len[0] = len[0] + 1;
    for (int i = 0; i < len[0]; i = i + 1) {
        out[i] = r[i];
    }
    return;
}
