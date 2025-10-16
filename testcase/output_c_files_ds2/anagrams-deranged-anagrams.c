int deranged(const char *s1, const char *s2)
{
    int i;
    for (i = 0; s1[i] != 0; i = i + 1)
    {
        if (s1[i] == s2[i])
        {
            return 0;
        }
    }
    return 1;
}

void count_letters_insert(int root_down[10][10], int root_list[10], const char *s, int cnt[26], int char_to_idx[128])
{
    int i;
    int len;
    int n;
    for (i = 0; i < 26; i = i + 1)
    {
        cnt[i] = 0;
    }
    len = 0;
    for (i = 0; s[i] != 0; i = i + 1)
    {
        if (s[i] < 'a' || s[i] > 'z')
        {
            return;
        }
        len = len + 1;
        cnt[char_to_idx[(unsigned char)s[i]]] = cnt[char_to_idx[(unsigned char)s[i]]] + 1;
    }
    for (i = 0; i < 5; i = i + 1)
    {
        n = cnt[i];
        if (root_down[i][n] == 0)
        {
            root_down[i][n] = 1;
        }
    }
    return;
}
