unsigned int mpow_ipow_gcd_lcm_multi_order_p_multi_order(unsigned int a, unsigned int p, unsigned int m) {
    unsigned int r;
    unsigned int t;
    unsigned int g;
    unsigned int fac[10000];
    unsigned int m_local;
    unsigned int t_local;
    unsigned int res;
    int i;
    int len;
    
    r = 1;
    for (; p; p = p >> 1) {
        if ((1 & p)) {
            r = r * a % m;
        }
        a = a * a % m;
    }
    
    r = 1;
    for (; p; p = p >> 1) {
        if ((1 & p)) {
            r = r * a;
        }
        a = a * a;
    }
    
    for (; m; ) {
        t = m;
        m = n % m;
        n = t;
    }
    
    g = gcd(m, n);
    res = m / g * n;
    
    m_local = ipow(p, e);
    t_local = m_local / p * (p - 1);
    len = get_factors(t_local, fac);
    for (i = 0; i < len; i = i + 1) {
        if (mpow(a, fac[i], m_local) == 1) {
            return fac[i];
        }
    }
    
    len = get_prime_factors(m, pf);
    res = 1;
    for (i = 0; i < len; i = i + 1) {
        res = lcm(res, multi_order_p(a, pf[i].p, pf[i].e));
    }
    
    return res;
    return;
}
