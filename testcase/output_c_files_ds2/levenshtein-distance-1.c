int levenshtein(const char *s, int ls, const char *t, int lt)
{
    int a[5];
    int b[5];
    int c[5];
    
    if (ls == 0)
    {
        return lt;
    }
    if (lt == 0)
    {
        return ls;
    }
    
    if (s[ls - 1] == t[lt - 1])
    {
        return levenshtein(s, ls - 1, t, lt - 1);
    }
    
    a[0] = levenshtein(s, ls - 1, t, lt - 1);
    b[0] = levenshtein(s, ls, t, lt - 1);
    c[0] = levenshtein(s, ls - 1, t, lt);
    
    if (a[0] > b[0])
    {
        a[0] = b[0];
    }
    if (a[0] > c[0])
    {
        a[0] = c[0];
    }
    
    return a[0] + 1;
}
