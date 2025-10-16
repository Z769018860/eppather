void func() {
    int inf[5];
    int minus_inf[5];
    int minus_zero[5];
    int nan[5];
    int temp[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        inf[i] = 0;
        minus_inf[i] = 0;
        minus_zero[i] = 0;
        nan[i] = 0;
        temp[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        minus_zero[i] = temp[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        nan[i] = temp[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = temp[i] + 2;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = temp[i] - 101;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = temp[i] + minus_inf[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = temp[i] * inf[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = temp[i] / minus_zero[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = nan[i] + 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = nan[i] + nan[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = (nan[i] == nan[i]) ? 1 : 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[i] = (0 == minus_zero[i]) ? 1 : 0;
    }
    
    return;
}
