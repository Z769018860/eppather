int get_mode(int* x, int len, int list[100][2]) {
    int i;
    int j;
    int temp;
    int vc[100][2];
    int count;
    
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (x[i] > x[j]) {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    
    count = 1;
    for (i = 0; i < len - 1; i = i + 1) {
        if (x[i] != x[i + 1]) {
            count = count + 1;
        }
    }
    
    vc[0][0] = x[0];
    vc[0][1] = 1;
    j = 0;
    for (i = 0; i < len - 1; i = i + 1) {
        if (x[i] != x[i + 1]) {
            j = j + 1;
            vc[j][0] = x[i + 1];
            vc[j][1] = 0;
        }
        vc[j][1] = vc[j][1] + 1;
    }
    
    for (i = 0; i < count; i = i + 1) {
        for (j = i + 1; j < count; j = j + 1) {
            if (vc[i][1] < vc[j][1]) {
                temp = vc[i][0];
                vc[i][0] = vc[j][0];
                vc[j][0] = temp;
                temp = vc[i][1];
                vc[i][1] = vc[j][1];
                vc[j][1] = temp;
            }
        }
    }
    
    i = 0;
    while (i < count && vc[i][1] == vc[0][1]) {
        i = i + 1;
    }
    
    for (j = 0; j < i; j = j + 1) {
        list[j][0] = vc[j][0];
        list[j][1] = vc[j][1];
    }
    
    return i;
}
