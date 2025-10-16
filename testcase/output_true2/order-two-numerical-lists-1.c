int list_cmp(int a[5], int la, int b[5], int lb)
{
    int i;
    int l[5];
    l[0] = la;
    if (l[0] > lb)
    {
        l[0] = lb;
    }
    for (i = 0; i < l[0]; i = i + 1)
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
