int palindrome(const char *s)
{
    const char *t;
    for (t = s; *t != '\0'; t = t + 1)
    {
    }
    t = t - 1;
    for (; s < t; )
    {
        if (*s != *t)
        {
            return 0;
        }
        s = s + 1;
        t = t - 1;
    }
    return 1;
}
