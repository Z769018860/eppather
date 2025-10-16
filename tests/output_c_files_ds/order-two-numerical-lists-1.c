int list_cmp(int *a, int la, int *b, int lb)
{
    int i;
    int l = la;
    if (l > lb)
    {
        l = lb;
    }
    for (i = 0; i < l; i = i + 1)
    {
        if (a[i] == b[i])
        {
            continue;
        }
        if (a[i] > b[i])
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    if (la == lb)
    {
        return 0;
    }
    if (la > lb)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    return;
}
