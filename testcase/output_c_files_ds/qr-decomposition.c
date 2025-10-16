void householder(int m_m, int m_n, double m_v[5][3], double R_v[5][3], double Q_v[5][5])
{
    double q_v[5][5][5][5];
    double z_v[5][3];
    double z1_v[5][3];
    int k;
    int i;
    int j;
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_n; j = j + 1)
        {
            z_v[i][j] = m_v[i][j];
        }
    }
    
    for (k = 0; k < m_n && k < m_m - 1; k = k + 1)
    {
        double e[5];
        double x[5];
        double a;
        double temp;
        
        for (i = 0; i < m_m; i = i + 1)
        {
            for (j = 0; j < m_n; j = j + 1)
            {
                if (i >= k && j >= k)
                {
                    z1_v[i][j] = z_v[i][j];
                }
                else if (i == j)
                {
                    z1_v[i][j] = 1.0;
                }
                else
                {
                    z1_v[i][j] = 0.0;
                }
            }
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            x[i] = z1_v[i][k];
        }
        
        temp = 0.0;
        for (i = 0; i < m_m; i = i + 1)
        {
            temp = temp + x[i] * x[i];
        }
        a = sqrt(temp);
        
        if (m_v[k][k] > 0)
        {
            a = -a;
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            e[i] = (i == k) ? 1.0 : 0.0;
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            e[i] = x[i] + a * e[i];
        }
        
        temp = 0.0;
        for (i = 0; i < m_m; i = i + 1)
        {
            temp = temp + e[i] * e[i];
        }
        temp = sqrt(temp);
        
        for (i = 0; i < m_m; i = i + 1)
        {
            e[i] = e[i] / temp;
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            for (j = 0; j < m_m; j = j + 1)
            {
                q_v[k][i][j] = -2.0 * e[i] * e[j];
            }
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            q_v[k][i][i] = q_v[k][i][i] + 1.0;
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            for (j = 0; j < m_n; j = j + 1)
            {
                temp = 0.0;
                for (int l = 0; l < m_m; l = l + 1)
                {
                    temp = temp + q_v[k][i][l] * z1_v[l][j];
                }
                z_v[i][j] = temp;
            }
        }
    }
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_n; j = j + 1)
        {
            temp = 0.0;
            for (int l = 0; l < m_m; l = l + 1)
            {
                temp = temp + q_v[0][i][l] * m_v[l][j];
            }
            R_v[i][j] = temp;
        }
    }
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_m; j = j + 1)
        {
            Q_v[i][j] = q_v[0][i][j];
        }
    }
    
    for (k = 1; k < m_n && k < m_m - 1; k = k + 1)
    {
        double temp_q[5][5];
        
        for (i = 0; i < m_m; i = i + 1)
        {
            for (j = 0; j < m_m; j = j + 1)
            {
                temp = 0.0;
                for (int l = 0; l < m_m; l = l + 1)
                {
                    temp = temp + q_v[k][i][l] * Q_v[l][j];
                }
                temp_q[i][j] = temp;
            }
        }
        
        for (i = 0; i < m_m; i = i + 1)
        {
            for (j = 0; j < m_m; j = j + 1)
            {
                Q_v[i][j] = temp_q[i][j];
            }
        }
    }
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_n; j = j + 1)
        {
            temp = 0.0;
            for (int l = 0; l < m_m; l = l + 1)
            {
                temp = temp + Q_v[l][i] * m_v[l][j];
            }
            z_v[i][j] = temp;
        }
    }
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_n; j = j + 1)
        {
            R_v[i][j] = z_v[i][j];
        }
    }
    
    for (i = 0; i < m_m; i = i + 1)
    {
        for (j = 0; j < m_m; j = j + 1)
        {
            temp = Q_v[i][j];
            Q_v[i][j] = Q_v[j][i];
            Q_v[j][i] = temp;
        }
    }
    
    return;
}
