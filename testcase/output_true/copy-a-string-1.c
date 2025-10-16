int copy_strings(int n) {
    int src[5] = {'H', 'e', 'l', 'l', 'o'};
    int dst1[80];
    int dst2[80];
    int dst3[5];
    int ref[5];
    int len;
    int i;

    for (i = 0; i < 5; i = i + 1) {
        dst1[i] = src[i];
    }
    dst1[5] = 0;

    len = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (src[i] != 0) {
            len = len + 1;
        }
    }

    if (len >= 80) {
        return;
    }

    for (i = 0; i < len; i = i + 1) {
        dst2[i] = src[i];
    }
    dst2[len] = 0;

    for (i = 0; i < 5; i = i + 1) {
        dst3[i] = src[i];
    }
    dst3[5] = 0;

    for (i = 0; i < 5; i = i + 1) {
        ref[i] = src[i];
    }

    for (i = 0; i < 5; i = i + 1) {
        src[i] = '-';
    }

    return;
}
