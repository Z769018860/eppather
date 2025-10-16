int str_cmp(int l_len, int l_alloc, int l_s[5], int r_len, int r_alloc, int r_s[5])
{
    int res;
    int len;
    len = l_len;
    if (len > r_len)
    {
        len = r_len;
    }
    for (int i = 0; i < len; i = i + 1)
    {
        if (l_s[i] != r_s[i])
        {
            res = l_s[i] - r_s[i];
            return res;
        }
    }
    if (l_len > r_len)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    return;
}
