int s_match(int a[5], int b[5]) {
    int i[5];
    int count[5];
    int c1[5];
    int c2[5];
    int result[5];
    i[0] = 0;
    count[0] = 0;
    for (; a[i[0]] != 0; i[0] = i[0] + 1) {
        c1[0] = a[i[0]];
        c2[0] = b[0];
        result[0] = 0;
        for (; c1[0] == c2[0]; ) {
            c1[0] = a[i[0]];
            if (0 == (c2[0] = b[0])) {
                if (c1[0] == 0) {
                    result[0] = -1;
                } else {
                    result[0] = 1;
                }
                break;
            }
            i[0] = i[0] + 1;
        }
        if (result[0] == -1) {
            count[0] = count[0] + 1;
            return count[0];
        } else {
            if (result[0] == 1) {
                count[0] = count[0] + 1;
            }
        }
    }
    return count[0];
}
