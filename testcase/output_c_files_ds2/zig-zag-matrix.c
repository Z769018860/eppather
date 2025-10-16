int func(int m) {
    int s[25];
    int i;
    int j;
    int n;
    int i1;
    int j1;
    int temp;
    
    n = 0;
    for (i = 0; i < 10; i = i + 1) {
        if (i < 5) {
            j1 = 0;
        } else {
            j1 = i - 5 + 1;
        }
        for (j = j1; j <= i; j = j + 1) {
            if (j < 5) {
                if ((i & 1) != 0) {
                    temp = j * (5 - 1) + i;
                } else {
                    temp = (i - j) * 5 + j;
                }
                s[temp] = n;
                n = n + 1;
            }
        }
    }
    return;
}
