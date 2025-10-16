void perm_sort(int a[5], int n, int msize, int (*_cmp)(int[5], int[5]))
{
    int tmp[5];
    int p[5];
    int q[5];
    int i;
    int j;
    int k;
    int l;
    int m;
    
    for (i = 0; i < 5; i = i + 1)
    {
        tmp[i] = 0;
        p[i] = 0;
        q[i] = 0;
    }
    
    while (1)
    {
        for (k = n - 1; k > 0; k = k - 1)
        {
            if (_cmp(a + (k - 1) * msize, a + k * msize) > 0)
            {
                break;
            }
        }
        
        if (k <= 0)
        {
            break;
        }
        
        for (l = n - 1; l > k - 1; l = l - 1)
        {
            if (_cmp(a + (k - 1) * msize, a + l * msize) > 0)
            {
                break;
            }
        }
        
        for (i = 0; i < 5; i = i + 1)
        {
            tmp[i] = a[(k - 1) * msize + i];
            a[(k - 1) * msize + i] = a[l * msize + i];
            a[l * msize + i] = tmp[i];
        }
        
        for (i = k, j = n - 1; i < j; i = i + 1, j = j - 1)
        {
            for (m = 0; m < 5; m = m + 1)
            {
                tmp[m] = a[i * msize + m];
                a[i * msize + m] = a[j * msize + m];
                a[j * msize + m] = tmp[m];
            }
        }
    }
    
    return;
}

int scmp(int a[5], int b[5])
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        if (a[i] != b[i])
        {
            return a[i] - b[i];
        }
    }
    return 0;
}
