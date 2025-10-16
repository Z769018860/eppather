int nub(int a[5], int n)
{
    int m;
    int i;
    int j;
    int found;
    
    m = 0;
    for (i = 0; i < n; i = i + 1)
    {
        found = 0;
        for (j = 0; j < m; j = j + 1)
        {
            if (a[j] == a[i])
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            a[m] = a[i];
            m = m + 1;
        }
    }
    return m;
}

int nub_new(int b[5], int a[5], int n)
{
    int c[5];
    int m;
    int i;
    
    for (i = 0; i < n; i = i + 1)
    {
        c[i] = a[i];
    }
    m = nub(c, n);
    for (i = 0; i < m; i = i + 1)
    {
        b[i] = c[i];
    }
    return m;
}

void elem(int a[5], int n, int e)
{
    int i;
    
    for (i = 0; i < n; i = i + 1)
    {
        if (a[i] == e)
        {
            return;
        }
    }
    return;
}
