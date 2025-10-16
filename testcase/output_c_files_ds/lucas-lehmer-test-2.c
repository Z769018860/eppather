int is_prime_and_mersenne_prime(int p) {
    int prime;
    int to;
    int i;
    int j;
    long long unsigned m_p;
    long long unsigned s;
    
    if (p == 2) {
        return 1;
    }
    if (p <= 1 || p % 2 == 0) {
        return 0;
    }
    
    prime = 1;
    to = 0;
    for (i = 1; i <= p; i = i + 1) {
        if (i * i <= p) {
            to = i;
        }
    }
    
    for (i = 3; i <= to; i = i + 2) {
        if (p % i == 0) {
            prime = 0;
            break;
        }
    }
    
    if (prime == 0) {
        return 0;
    }
    
    m_p = 1;
    for (i = 1; i <= p; i = i + 1) {
        m_p = m_p * 2;
    }
    m_p = m_p - 1;
    
    s = 4;
    for (i = 3; i <= p; i = i + 1) {
        s = (s * s - 2) % m_p;
    }
    
    if (s == 0) {
        return 1;
    } else {
        return 0;
    }
    return;
}
