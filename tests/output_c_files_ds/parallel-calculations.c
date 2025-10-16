int func() {
    int data[7] = {12757923, 12878611, 12878893, 12757923, 15808973, 15780709, 197622519};
    int largest;
    int largest_factor = 0;
    int i;
    int p;
    int n;
    
    for (i = 0; i < 7; i = i + 1) {
        n = data[i];
        p = 3;
        
        for (; p * p <= n; p = p + 2) {
            if (n % p == 0) {
                break;
            }
        }
        
        if (p * p > n) {
            p = n;
        }
        
        if (p > largest_factor) {
            largest_factor = p;
            largest = n;
        }
    }
    
    return;
}
