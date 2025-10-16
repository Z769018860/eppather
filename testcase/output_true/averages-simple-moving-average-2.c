int sma_func(int n1, int n2, int n3, int v[10]) {
    int h3[5];
    int h5[5];
    int i;
    int j;
    int sum3;
    int sum5;
    int count3;
    int count5;
    
    for (i = 0; i < 5; i = i + 1) {
        h3[i] = 0;
        h5[i] = 0;
    }
    
    for (i = 0; i < 10; i = i + 1) {
        sum3 = 0;
        count3 = 0;
        for (j = 0; j < 3; j = j + 1) {
            if (i - j >= 0) {
                sum3 = sum3 + v[i - j];
                count3 = count3 + 1;
            }
        }
        h3[0] = sum3 / count3;
        
        sum5 = 0;
        count5 = 0;
        for (j = 0; j < 5; j = j + 1) {
            if (i - j >= 0) {
                sum5 = sum5 + v[i - j];
                count5 = count5 + 1;
            }
        }
        h5[0] = sum5 / count5;
    }
    
    return;
}
