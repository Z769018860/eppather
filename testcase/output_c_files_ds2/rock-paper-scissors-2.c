int weighed_rand(int tbl[5], int len)
{
    int i;
    int sum;
    int r;
    int rand_max;
    int ret;
    int n;
    sum = 0;
    for (i = 0; i < len; i = i + 1)
    {
        sum = sum + tbl[i];
    }
    if (sum == 0)
    {
        n = len;
        rand_max = 32767 - (32767 % n);
        while (1)
        {
            ret = 0;
            if (ret >= rand_max)
            {
                continue;
            }
            break;
        }
        return ret / (rand_max / n);
    }
    n = sum;
    rand_max = 32767 - (32767 % n);
    while (1)
    {
        ret = 0;
        if (ret >= rand_max)
        {
            continue;
        }
        break;
    }
    r = (ret / (rand_max / n)) + 1;
    for (i = 0; i < len; i = i + 1)
    {
        r = r - tbl[i];
        if (r > 0)
        {
            continue;
        }
        break;
    }
    return i;
}
