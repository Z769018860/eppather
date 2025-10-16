void do_base(int base, int small_primes[25], int MAX_STACK)
{
    int answer[5];
    int tens[128][5];
    int value[128][5];
    int seen_depth;
    int i;
    int d;
    int j;
    int k;
    int temp[5];
    int carry;
    int is_prime;
    int cmp_result;
    
    answer[0] = 0;
    tens[0][0] = 1;
    for (i = 1; i < 5; i = i + 1) {
        tens[0][i] = 0;
    }
    
    for (i = 1; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            tens[i][j] = 0;
        }
        carry = 0;
        for (j = 0; j < 5; j = j + 1) {
            temp[j] = tens[i-1][j] * base + carry;
            carry = temp[j] / 1000000000;
            tens[i][j] = temp[j] % 1000000000;
        }
    }
    
    seen_depth = 0;
    for (i = 0; i < 25; i = i + 1) {
        if (small_primes[i] >= base) {
            break;
        }
        for (j = 0; j < 5; j = j + 1) {
            value[0][j] = 0;
        }
        value[0][0] = small_primes[i];
        
        for (d = 1; d < base; d = d + 1) {
            for (j = 0; j < 5; j = j + 1) {
                value[1][j] = value[0][j];
            }
            carry = 0;
            for (j = 0; j < 5; j = j + 1) {
                temp[j] = value[1][j] + tens[1][j] * d + carry;
                carry = temp[j] / 1000000000;
                value[1][j] = temp[j] % 1000000000;
            }
            
            is_prime = 1;
            for (k = 2; k < value[1][0]; k = k + 1) {
                if (value[1][0] % k == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime == 0) {
                continue;
            }
            
            cmp_result = 0;
            for (j = 4; j >= 0; j = j - 1) {
                if (value[1][j] > answer[j]) {
                    cmp_result = 1;
                    break;
                } else if (value[1][j] < answer[j]) {
                    cmp_result = -1;
                    break;
                }
            }
            
            if (1 > seen_depth || (1 == seen_depth && cmp_result == 1)) {
                is_prime = 1;
                for (k = 2; k < value[1][0]; k = k + 1) {
                    if (value[1][0] % k == 0) {
                        is_prime = 0;
                        break;
                    }
                }
                if (is_prime == 0) {
                    continue;
                }
                
                for (j = 0; j < 5; j = j + 1) {
                    answer[j] = value[1][j];
                }
                seen_depth = 1;
            }
        }
    }
    return;
}
