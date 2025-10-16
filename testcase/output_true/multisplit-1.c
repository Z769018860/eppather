void parse_sep(const char *str, const char *const *pat, int len)
{
    int i;
    int slen[5];
    int j;
    int k;
    int n;
    int n1;
    int n2;
    int n3;
    int n4;
    n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    for (n = 0; n < 5; n = n + 1)
    {
        slen[n] = 0;
    }
    for (; str[n1] != 0; n1 = n1 + 1)
    {
        for (i = 0; i < len; i = i + 1)
        {
            for (n2 = 0; pat[i][n2] != 0; n2 = n2 + 1)
            {
            }
            slen[0] = n2;
            for (j = 0; j < slen[0]; j = j + 1)
            {
                if (str[n1 + j] != pat[i][j])
                {
                    break;
                }
            }
            if (j == slen[0])
            {
                n1 = n1 + slen[0];
                break;
            }
        }
    }
    return;
}
