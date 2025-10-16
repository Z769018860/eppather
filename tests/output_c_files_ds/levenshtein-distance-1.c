int levenshtein(const char *s, int ls, const char *t, int lt)
{
    int a;
    int b;
    int c;
    int result;
    
    if (ls == 0)
    {
        result = lt;
        return result;
    }
    
    if (lt == 0)
    {
        result = ls;
        return result;
    }
    
    if (s[ls - 1] == t[lt - 1])
    {
        result = levenshtein(s, ls - 1, t, lt - 1);
        return result;
    }
    
    a = levenshtein(s, ls - 1, t, lt - 1);
    b = levenshtein(s, ls, t, lt - 1);
    c = levenshtein(s, ls - 1, t, lt);
    
    if (a > b)
    {
        a = b;
    }
    
    if (a > c)
    {
        a = c;
    }
    
    result = a + 1;
    return result;
}
