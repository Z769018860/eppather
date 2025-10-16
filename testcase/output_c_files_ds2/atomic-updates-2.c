void bucket_transfer(int bucket_size, int iterations) {
    int bucket[10];
    int i;
    for (i = 0; i < 10; i = i + 1) {
        bucket[i] = 1000;
    }
    
    for (i = 0; i < iterations; i = i + 1) {
        int from;
        int to;
        int mode;
        int diff = 0;
        int sum;
        int j;
        
        from = i % 10;
        to = (i + 1) % 10;
        if (from == to) {
            to = (to + 1) % 10;
        }
        mode = i % 10;
        
        if (mode == 0 || mode == 1 || mode == 2) {
            diff = (bucket[from] - bucket[to]) / 2;
        } else if (mode == 3) {
            sum = 0;
            for (j = 0; j < 10; j = j + 1) {
                sum = sum + bucket[j];
            }
        } else {
            diff = bucket[from] % 100;
        }
        
        bucket[from] = bucket[from] - diff;
        bucket[to] = bucket[to] + diff;
    }
    return;
}
