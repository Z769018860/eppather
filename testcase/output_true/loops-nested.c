int func(int n1, int n2) {
    int a[5][5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            a[i][j] = (i * 5 + j) % 20 + 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (a[i][j] == 20) {
                return;
            }
        }
    }
    
    return;
}
