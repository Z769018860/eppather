int func(int n1, int n2) {
    int q[5];
    int flip[5];
    int i;
    
    q[1] = 1;
    q[2] = 1;
    
    for (i = 3; i <= 5; i = i + 1) {
        q[i] = q[i - q[i - 1]] + q[i - q[i - 2]];
    }
    
    flip[0] = 0;
    for (i = 1; i < 5; i = i + 1) {
        if (q[i] > q[i + 1]) {
            flip[0] = flip[0] + 1;
        }
    }
    
    return;
}
