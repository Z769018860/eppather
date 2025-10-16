int palindrome(const char *s, int n1)
{
    int i[5];
    int l[5];
    l[0] = 0;
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        if (s[i[0]] == 0)
        {
            break;
        }
        l[0] = l[0] + 1;
    }
    for (i[0] = 0; i[0] < l[0] / 2; i[0] = i[0] + 1)
    {
        if (s[i[0]] != s[l[0] - i[0] - 1])
        {
            return 0;
        }
    }
    return 1;
    return;
}
