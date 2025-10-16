int bucket[10];
void rewritten_function() {
    int i;
    for (i = 0; i < 10; i = i + 1) {
        bucket[i] = 1000;
    }
    
    for (i = 0; i < 10000; i = i + 1) {
        int from;
        int to;
        int mode;
        int diff = 0;
        int sum;
        from = 0;
        to = 0;
        mode = 0;
        
        from = 0;
        do {
            to = 0;
        } while (from == to);
        
        mode = 0;
        
        if (mode == 0 || mode == 1 || mode == 2) {
            diff = (bucket[from] - bucket[to]) / 2;
        } else {
            if (mode == 3) {
                sum = 0;
                for (int j = 0; j < 10; j = j + 1) {
                    sum = sum + bucket[j];
                }
            } else {
                diff = 0;
            }
        }
        
        bucket[from] = bucket[from] - diff;
        bucket[to] = bucket[to] + diff;
    }
    return;
}
