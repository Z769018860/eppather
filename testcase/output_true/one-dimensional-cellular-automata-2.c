int evolve(int c[5], int len, int trans[5])
{
    int i;
    int diff = 0;
    int v[5];
    for (i = 0; i < 5; i = i + 1)
    {
        if (c[i] == 35)
        {
            c[i] = 1;
        }
        else
        {
            c[i] = 0;
        }
    }
    for (i = 0; i < 5; i = i + 1)
    {
        if (i > 0)
        {
            if ((c[i - 1] & 15) == 1)
            {
                v[0] = 1;
            }
            else
            {
                v[0] = 0;
            }
        }
        else
        {
            v[0] = 0;
        }
        if ((c[i] & 15) == 1)
        {
            v[1] = 1;
        }
        else
        {
            v[1] = 0;
        }
        if (i < 4)
        {
            if ((c[i + 1] & 15) == 1)
            {
                v[2] = 1;
            }
            else
            {
                v[2] = 0;
            }
        }
        else
        {
            v[2] = 0;
        }
        if (trans[v[0] * 4 + v[1] * 2 + v[2]] == 35)
        {
            c[i] = c[i] | (1 << 4);
        }
    }
    for (i = 0; i < 5; i = i + 1)
    {
        diff = diff + ((c[i] & 15) ^ (c[i] >> 4));
    }
    for (i = 0; i < 5; i = i + 1)
    {
        if ((c[i] >> 4) != 0)
        {
            c[i] = 35;
        }
        else
        {
            c[i] = 95;
        }
    }
    return diff;
}
