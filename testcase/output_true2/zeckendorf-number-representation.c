int fibbinary(int n, int fib[65])
{
    int ret;
    int i;
    int n1;
    
    n1 = 64;
    if (n >= fib[n1])
    {
        ret = -1;
        return ret;
    }
    
    ret = 0;
    for (i = n1; i >= 0; i = i - 1)
    {
        if (n >= fib[i])
        {
            ret = ret | (1 << i);
            n = n - fib[i];
        }
    }
    
    return ret;
}

void bprint(int n, int width)
{
    int b;
    int n1;
    
    n1 = 64;
    if (width > n1)
    {
        width = n1;
    }
    
    b = 1 << (width - 1);
    for (; b != 0; b = b >> 1)
    {
        if (b == 1 && n == 0)
        {
        }
        else if (b > n)
        {
        }
        else if (b & n)
        {
        }
        else
        {
        }
    }
    
    return;
}

void merged_function(int n, int width, int fib[65])
{
    int ret;
    int i;
    int n1;
    int b;
    
    n1 = 64;
    if (n >= fib[n1])
    {
        ret = -1;
    }
    else
    {
        ret = 0;
        for (i = n1; i >= 0; i = i - 1)
        {
            if (n >= fib[i])
            {
                ret = ret | (1 << i);
                n = n - fib[i];
            }
        }
    }
    
    if (width > n1)
    {
        width = n1;
    }
    
    b = 1 << (width - 1);
    for (; b != 0; b = b >> 1)
    {
        if (b == 1 && n == 0)
        {
        }
        else if (b > n)
        {
        }
        else if (b & n)
        {
        }
        else
        {
        }
    }
    
    return;
}
