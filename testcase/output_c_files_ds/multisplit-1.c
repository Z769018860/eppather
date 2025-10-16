void parse_sep(const char *str, const char *const *pat, int len)
{
    int i;
    int j;
    int slen;
    int match;
    for (; *str != '\0'; str = str + 1)
    {
        for (i = 0; i < len; i = i + 1)
        {
            slen = 0;
            for (j = 0; pat[i][j] != '\0'; j = j + 1)
            {
                slen = slen + 1;
            }
            match = 1;
            for (j = 0; j < slen; j = j + 1)
            {
                if (str[j] != pat[i][j])
                {
                    match = 0;
                    break;
                }
            }
            if (match)
            {
                str = str + slen;
                break;
            }
        }
    }
    return;
}
