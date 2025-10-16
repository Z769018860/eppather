int action_merge(int size) {
    int res[5];
    res[0] = 0;
    return res[0];
}

int action_qsort(int size) {
    int res[5];
    res[0] = 0;
    return res[0];
}

int get_the_longest(int a[5]) {
    int r[5];
    int i[5];
    r[0] = a[0];
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (a[i[0]] > 0) {
            if (a[i[0]] > r[0]) {
                r[0] = a[i[0]];
            }
        }
    }
    return r[0];
}

void main() {
    int i[5];
    int j[5];
    int k[5];
    int z[5];
    int lenmax[5];
    int buf[5];
    int out[5];
    int thetime[5];
    int datlengths[5] = {100, 200, 300, 500, 1000};
    int tobesorted[5];
    
    lenmax[0] = get_the_longest(datlengths);
    tobesorted[0] = 0;
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
            for (k[0] = 0; k[0] < 5; k[0] = k[0] + 1) {
                thetime[0] = 0;
                for (z[0] = 0; z[0] < 5; z[0] = z[0] + 1) {
                    thetime[0] = thetime[0] + 1;
                }
                thetime[0] = thetime[0] / 5;
            }
        }
    }
    return;
}
