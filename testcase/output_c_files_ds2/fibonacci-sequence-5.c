int find_cache(int n, int cache_n[37], int cache_v[37][5], int cache_next[37], int tmp1[5], int tmp2[5]) {
    int idx = n % 37;
    int p = cache_next[idx];
    
    for (; p != 0 && cache_n[p] != n; p = cache_next[p]) {
    }
    
    if (p != 0) {
        return p;
    }
    
    p = 1;
    cache_next[p] = cache_next[idx];
    cache_next[idx] = p;
    
    if (n < 2) {
        cache_n[p] = n;
        cache_v[p][0] = 1;
    } else {
        cache_n[p] = -1;
        cache_v[p][0] = 0;
    }
    return p;
}

void fib(int n, int cache_n[37], int cache_v[37][5], int cache_next[37], int tmp1[5], int tmp2[5]) {
    int x;
    int p = find_cache(n, cache_n, cache_v, cache_next, tmp1, tmp2);
    
    if (cache_n[p] < 0) {
        cache_n[p] = n;
        x = n / 2;
        
        fib(x - 1, cache_n, cache_v, cache_next, tmp1, tmp2);
        fib(n - x - 1, cache_n, cache_v, cache_next, tmp1, tmp2);
        tmp1[0] = cache_v[x - 1][0] * cache_v[n - x - 1][0];
        
        fib(x, cache_n, cache_v, cache_next, tmp1, tmp2);
        fib(n - x, cache_n, cache_v, cache_next, tmp1, tmp2);
        tmp2[0] = cache_v[x][0] * cache_v[n - x][0];
        
        cache_v[p][0] = tmp1[0] + tmp2[0];
    }
    return;
}
