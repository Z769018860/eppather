void binprint(unsigned int n, unsigned int m)
{
    char c[32];
    int i;
    int m1;
    m1 = m;
    for (i = 0; i < 32; i = i + 1)
    {
        if (m1 != 0)
        {
            if ((n & m1) != 0)
            {
                c[i] = 35;
            }
            else
            {
                c[i] = 45;
            }
            m1 = m1 >> 1;
        }
        else
        {
            c[i] = 0;
            break;
        }
    }
    return;
}

void func(unsigned int n1, unsigned int n2, unsigned int n3, unsigned int n4)
{
    unsigned int n[5];
    unsigned int gap[5];
    unsigned int left[5];
    unsigned int right[5];
    n[0] = n1;
    gap[0] = n2;
    left[0] = n3;
    right[0] = n4;
    
    for (gap[0] = 2; gap[0] < n[0]; gap[0] = gap[0] << 1)
    {
        for (left[0] = gap[0] << 1; left[0] < n[0]; left[0] = left[0] | (left[0] << 1))
        {
            for (right[0] = 1; right[0] < gap[0]; right[0] = right[0] + 1)
            {
                binprint(left[0] | right[0], n[0]);
            }
        }
    }
    return;
}
