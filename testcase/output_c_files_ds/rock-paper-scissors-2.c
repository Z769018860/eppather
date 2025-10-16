int weighed_rand(int *tbl, int len)
{
    int sum;
    int r;
    int i;
    sum = 0;
    for (i = 0; i < len; i = i + 1)
    {
        sum = sum + tbl[i];
    }
    if (sum == 0)
    {
        int rand_max;
        int ret;
        rand_max = 32767 - (32767 % len);
        ret = 0;
        while (ret >= rand_max)
        {
            ret = 0;
        }
        return ret / (rand_max / len);
    }
    r = 0;
    while (r >= sum)
    {
        r = 0;
    }
    r = r + 1;
    i = 0;
    while (i < len && r > 0)
    {
        r = r - tbl[i];
        if (r > 0)
        {
            i = i + 1;
        }
    }
    return i;
}
