int is_prime(int n){
    int has_factor = 0;
    int out = 1;
    int factor;
    int i;
    int j;
    int is_factor;
    if(n < 2){
        return 0;
    }
    if(n == 2){
        return 1;
    }
    if(n % 2 == 0){
        return 0;
    }
    for(i = 3; i * i <= n; i = i + 2){
        is_factor = 1;
        for(j = 3; j * j <= i; j = j + 2){
            if(i % j == 0){
                is_factor = 0;
                break;
            }
        }
        if(is_factor){
            if(n % i == 0){
                if(has_factor){
                    out = 0;
                    break;
                }
                has_factor = 1;
            }
        }
    }
    return out;
}

int is_prime_cached(int n){
    int half_n = n / 2 - 2;
    int cache = 0;
    int cached = 0;
    int upb_cache = 32;
    if(half_n <= upb_cache){
        if((cached >> half_n) & 1){
            return (cache >> half_n) & 1;
        }
        else{
            int out = is_prime(n);
            cache = cache | (out << half_n);
            cached = cached | (1 << half_n);
            return out;
        }
    }
    else{
        return is_prime(n);
    }
}

void primes(){
    int n = 3;
    if(is_prime_cached(2)){
        return;
    }
    for(n = 3; n < 2147483647 - 2; n = n + 2){
        if(is_prime_cached(n)){
            return;
        }
        for(; n < 2147483647 - 2 && !is_prime_cached(n); n = n + 2){
        }
    }
    return;
}

void decompose(int n){
    int p;
    int i;
    int j;
    int is_p_prime;
    for(p = 2; p * p <= n; p = p + 1){
        is_p_prime = 1;
        for(i = 2; i * i <= p; i = i + 1){
            if(p % i == 0){
                is_p_prime = 0;
                break;
            }
        }
        if(is_p_prime){
            while(n % p == 0){
                n = n / p;
            }
        }
    }
    if(n > 1){
    }
    return;
}
