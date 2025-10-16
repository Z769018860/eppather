int func(int data[7]) {
    int largest[5];
    int largest_factor[5];
    largest_factor[0] = 0;
    largest[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        int p[5];
        int n[5];
        n[0] = data[i];
        
        p[0] = 3;
        for (; p[0] * p[0] <= n[0] && n[0] % p[0]; p[0] = p[0] + 2) {
        }
        if (p[0] * p[0] > n[0]) {
            p[0] = n[0];
        }
        if (p[0] > largest_factor[0]) {
            largest_factor[0] = p[0];
            largest[0] = n[0];
        }
    }
    return largest[0];
}
