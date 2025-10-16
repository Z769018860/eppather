int func() {
    int a[10][10];
    int i;
    int j;
    
    for (i = 0; i < 10; i = i + 1) {
        for (j = 0; j < 10; j = j + 1) {
            a[i][j] = 1;
        }
    }
    
    for (i = 0; i < 10; i = i + 1) {
        for (j = 0; j < 10; j = j + 1) {
            if (a[i][j] == 20) {
                return;
            }
        }
    }
    
    return;
}
