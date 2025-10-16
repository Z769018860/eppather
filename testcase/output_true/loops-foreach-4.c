void rewritten_function() {
    int c1[5] = {'c', 'o', 'l', 'l', 'e'};
    int c2[6] = {3, 1, 4, 1, 5, 9};
    int c3[4] = {1, 3, 5, 7};
    int p1[5];
    int p2[6];
    int p3[4];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        p1[i] = c1[i];
    }
    
    for (i = 0; i < 6; i = i + 1) {
        p2[i] = c2[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        p3[i] = c3[i];
    }
    
    return;
}
