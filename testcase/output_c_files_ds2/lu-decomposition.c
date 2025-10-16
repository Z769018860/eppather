void mat_LU(int A[5][5], int L[5][5], int U[5][5], int P[5][5], int n)
{
    for(int i=0;i<5;i=i+1)
    {
        for(int j=0;j<5;j=j+1)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }
    
    for(int i=0;i<5;i=i+1)
    {
        for(int j=0;j<5;j=j+1)
        {
            P[i][j] = (i == j);
        }
    }
    
    for(int i=0;i<5;i=i+1)
    {
        int max_j = i;
        for(int j=i;j<5;j=j+1)
        {
            int a_j_i = (A[j][i] < 0) ? -A[j][i] : A[j][i];
            int a_max_j_i = (A[max_j][i] < 0) ? -A[max_j][i] : A[max_j][i];
            if(a_j_i > a_max_j_i)
            {
                max_j = j;
            }
        }
        
        if(max_j != i)
        {
            for(int k=0;k<5;k=k+1)
            {
                int tmp = P[i][k];
                P[i][k] = P[max_j][k];
                P[max_j][k] = tmp;
            }
        }
    }
    
    int Aprime[5][5];
    for(int i=0;i<5;i=i+1)
    {
        for(int j=0;j<5;j=j+1)
        {
            Aprime[i][j] = 0;
            for(int k=0;k<5;k=k+1)
            {
                Aprime[i][j] = Aprime[i][j] + P[i][k] * A[k][j];
            }
        }
    }
    
    for(int i=0;i<5;i=i+1)
    {
        L[i][i] = 1;
    }
    
    for(int i=0;i<5;i=i+1)
    {
        for(int j=0;j<5;j=j+1)
        {
            if(j <= i)
            {
                int s = 0;
                for(int k=0;k<j;k=k+1)
                {
                    s = s + L[j][k] * U[k][i];
                }
                U[j][i] = Aprime[j][i] - s;
            }
            
            if(j >= i)
            {
                int s = 0;
                for(int k=0;k<i;k=k+1)
                {
                    s = s + L[j][k] * U[k][i];
                }
                L[j][i] = (Aprime[j][i] - s) / U[i][i];
            }
        }
    }
    
    return;
}
