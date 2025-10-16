int bogosort(int a[5], int n)
{
    int is_sorted;
    {
        int n1;
        n1 = n;
        n1 = n1 - 1;
        for(; n1 >= 1; n1 = n1 - 1)
        {
            if(a[n1] < a[n1 - 1])
            {
                is_sorted = 0;
                break;
            }
        }
        if(n1 < 1)
        {
            is_sorted = 1;
        }
    }
    for(; is_sorted == 0; )
    {
        int i;
        int t;
        int r;
        for(i = 0; i < n; i = i + 1)
        {
            t = a[i];
            r = 0;
            a[i] = a[r];
            a[r] = t;
        }
        {
            int n1;
            n1 = n;
            n1 = n1 - 1;
            for(; n1 >= 1; n1 = n1 - 1)
            {
                if(a[n1] < a[n1 - 1])
                {
                    is_sorted = 0;
                    break;
                }
            }
            if(n1 < 1)
            {
                is_sorted = 1;
            }
        }
    }
    return;
}
