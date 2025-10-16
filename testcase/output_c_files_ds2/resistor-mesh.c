int calc_diff(int m_v[5][5], int m_fixed[5][5], int d_v[5][5], int w, int h)
{
    int i;
    int j;
    int n;
    int v;
    int total = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            v = 0;
            n = 0;
            if (i != 0)
            {
                v = v + m_v[i - 1][j];
                n = n + 1;
            }
            if (j != 0)
            {
                v = v + m_v[i][j - 1];
                n = n + 1;
            }
            if (i + 1 < h)
            {
                v = v + m_v[i + 1][j];
                n = n + 1;
            }
            if (j + 1 < w)
            {
                v = v + m_v[i][j + 1];
                n = n + 1;
            }
            d_v[i][j] = m_v[i][j] - v / n;
            v = d_v[i][j];
            if (m_fixed[i][j] == 0)
            {
                total = total + v * v;
            }
        }
    }
    return total;
}

void set_boundary(int m_v[5][5], int m_fixed[5][5])
{
    m_fixed[1][1] = 1;
    m_v[1][1] = 1;
    m_fixed[6][7] = -1;
    m_v[6][7] = -1;
}

int iter(int m_v[5][5], int m_fixed[5][5], int w, int h)
{
    int d_v[5][5];
    int i;
    int j;
    int diff = 1000000000;
    int cur[3] = {0, 0, 0};

    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            d_v[i][j] = 0;
        }
    }

    while (diff > 0)
    {
        set_boundary(m_v, m_fixed);
        diff = calc_diff(m_v, m_fixed, d_v, w, h);
        for (i = 0; i < 5; i = i + 1)
        {
            for (j = 0; j < 5; j = j + 1)
            {
                m_v[i][j] = m_v[i][j] - d_v[i][j];
            }
        }
    }

    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            cur[m_fixed[i][j] + 1] = cur[m_fixed[i][j] + 1] + d_v[i][j] * ((i != 0 ? 1 : 0) + (j != 0 ? 1 : 0) + (i < h - 1 ? 1 : 0) + (j < w - 1 ? 1 : 0));
        }
    }
    return (cur[2] - cur[0]) / 2;
}

void alloc2(int a_v[5][5], int a_fixed[5][5], int w, int h)
{
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            a_v[i][j] = 0;
            a_fixed[i][j] = 0;
        }
    }
    return;
}
