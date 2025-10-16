int generate_random(int param) {
    int v[5];
    int result[5];
    result[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        v[i] = 0;
    }
    
    if (param == 0) {
        result[0] = 1;
    } else {
        for (int j = 0; j < 5; j = j + 1) {
            v[j] = v[j] + j * param;
        }
    }
    
    return;
}
