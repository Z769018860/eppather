int cache_n[37][100];
int cache_v[37][100];
int cache_next[37][100];
int cache_size[37];
int tmp1[100];
int tmp2[100];

int* find_cache(int n) {
    int idx = n % 37;
    int p;
    
    for (p = 0; p < cache_size[idx]; p = p + 1) {
        if (cache_n[idx][p] == n) {
            return cache_v[idx];
        }
    }
    
    if (cache_size[idx] < 100) {
        cache_next[idx][cache_size[idx]] = cache_size[idx];
        cache_n[idx][cache_size[idx]] = n;
        
        if (n < 2) {
            cache_v[idx][cache_size[idx]] = 1;
        } else {
            cache_n[idx][cache_size[idx]] = -1;
            cache_v[idx][cache_size[idx]] = 0;
        }
        cache_size[idx] = cache_size[idx] + 1;
    }
    return cache_v[idx];
}

int* fib(int n) {
    int x;
    int* p = find_cache(n);
    
    if (p[0] < 0) {
        p[0] = n;
        x = n / 2;
        
        int* f1 = fib(x - 1);
        int* f2 = fib(n - x - 1);
        for (int i = 0; i < 100; i = i + 1) {
            tmp1[i] = f1[i] * f2[i];
        }
        
        int* f3 = fib(x);
        int* f4 = fib(n - x);
        for (int i = 0; i < 100; i = i + 1) {
            tmp2[i] = f3[i] * f4[i];
        }
        
        for (int i = 0; i < 100; i = i + 1) {
            p[i] = tmp1[i] + tmp2[i];
        }
    }
    return p;
}

return;
