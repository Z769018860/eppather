int is_prime_and_mersenne_prime(int p, int upb) {
    int result[5];
    result[0] = 0;
    if (p == 2) {
        result[0] = 1;
    } else {
        if (p <= 1 || p % 2 == 0) {
            result[0] = 0;
        } else {
            int prime[5];
            prime[0] = 1;
            int to[5];
            to[0] = 0;
            int i[5];
            for (i[0] = 1; i[0] <= p; i[0] = i[0] + 1) {
                if (i[0] * i[0] <= p) {
                    to[0] = i[0];
                }
            }
            for (i[0] = 3; i[0] <= to[0]; i[0] = i[0] + 2) {
                if (p % i[0] == 0) {
                    prime[0] = 0;
                    break;
                }
            }
            if (prime[0] == 1) {
                long long unsigned m_p[5];
                m_p[0] = 1;
                int j[5];
                for (j[0] = 0; j[0] < p; j[0] = j[0] + 1) {
                    m_p[0] = m_p[0] * 2;
                }
                m_p[0] = m_p[0] - 1;
                long long unsigned s[5];
                s[0] = 4;
                for (i[0] = 3; i[0] <= p; i[0] = i[0] + 1) {
                    s[0] = (s[0] * s[0] - 2) % m_p[0];
                }
                if (s[0] == 0) {
                    result[0] = 1;
                }
            }
        }
    }
    return result[0];
}
