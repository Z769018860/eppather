int grep(int in[5], int len, int outlen[5], int sel(int), int inplace, int out[5]) {
    int i;
    int j;
    int temp[5];
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = in[i];
    }
    j = 0;
    for (i = 0; i < len; i = i + 1) {
        if (sel(temp[i])) {
            out[j] = temp[i];
            j = j + 1;
        }
    }
    outlen[0] = j;
    return;
}

int even_sel(int x[5]) {
    if ((x[0] & 1) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int tri_sel(int x[5]) {
    if ((x[0] % 3) != 0) {
        return 1;
    } else {
        return 0;
    }
}
