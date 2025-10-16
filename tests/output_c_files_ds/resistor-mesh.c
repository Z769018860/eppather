int calc_diff(int m_v[10][10], int m_fixed[10][10], int d_v[10][10], int w, int h) {
    int i;
    int j;
    int n;
    int v;
    int total = 0;
    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            v = 0;
            n = 0;
            if (i != 0) {
                v = v + m_v[i - 1][j];
                n = n + 1;
            }
            if (j != 0) {
                v = v + m_v[i][j - 1];
                n = n + 1;
            }
            if (i + 1 < h) {
                v = v + m_v[i + 1][j];
                n = n + 1;
            }
            if (j + 1 < w) {
                v = v + m_v[i][j + 1];
                n = n + 1;
            }
            d_v[i][j] = v = m_v[i][j] - v / n;
            if (m_fixed[i][j] == 0) {
                total = total + v * v;
            }
        }
    }
    return total;
}

void iter(int m_v[10][10], int m_fixed[10][10], int w, int h) {
    int d_v[10][10];
    int i;
    int j;
    int diff = 1000000000;
    int cur[3] = {0, 0, 0};
    
    for (i = 0; i < 10; i = i + 1) {
        for (j = 0; j < 10; j = j + 1) {
            d_v[i][j] = 0;
        }
    }
    
    m_fixed[1][1] = 1;
    m_v[1][1] = 1;
    m_fixed[6][7] = -1;
    m_v[6][7] = -1;
    
    while (diff > 0) {
        m_fixed[1][1] = 1;
        m_v[1][1] = 1;
        m_fixed[6][7] = -1;
        m_v[6][7] = -1;
        diff = calc_diff(m_v, m_fixed, d_v, w, h);
        for (i = 0; i < h; i = i + 1) {
            for (j = 0; j < w; j = j + 1) {
                m_v[i][j] = m_v[i][j] - d_v[i][j];
            }
        }
    }
    
    for (i = 0; i < h; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            cur[m_fixed[i][j] + 1] = cur[m_fixed[i][j] + 1] + d_v[i][j] * ((i != 0 ? 1 : 0) + (j != 0 ? 1 : 0) + (i < h - 1 ? 1 : 0) + (j < w - 1 ? 1 : 0));
        }
    }
    
    return;
}
