int repstr(char str[5])
{
    int sl;
    int i;
    int j;
    int k;
    int match;
    
    if (!str) 
    {
        return 0;
    }
    
    sl = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (str[i] == 0)
        {
            break;
        }
        sl = sl + 1;
    }
    sl = sl / 2;
    
    for (; sl > 0; sl = sl - 1)
    {
        match = 1;
        for (j = 0; j < sl; j = j + 1)
        {
            if (str[j] != str[j + sl])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            return sl;
        }
    }
    
    return 0;
}
