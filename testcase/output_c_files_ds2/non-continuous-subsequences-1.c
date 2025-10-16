int func(int c, char** v) {
    int n[5];
    n[0] = 1;
    int i;
    for (i = 0; i < c - 1; i = i + 1) {
        n[0] = n[0] * 2;
    }
    int j[5];
    int k[5];
    i = n[0];
    
    for (; i > 0; i = i - 1) {
        int temp1[5];
        temp1[0] = -i;
        temp1[0] = i & temp1[0];
        temp1[0] = i + temp1[0];
        if (!(i & temp1[0])) {
            continue;
        }
        
        j[0] = n[0];
        k[0] = 1;
        for (; j[0] > 0; j[0] = j[0] / 2) {
            if (i & j[0]) {
                int temp2[5];
                temp2[0] = 0;
            }
            k[0] = k[0] + 1;
        }
    }
    return 0;
}
