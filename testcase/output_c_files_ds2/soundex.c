void soundex(int s[5], int out[5], int code[128])
{
    int c;
    int prev;
    int i;
    int j;
    
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
    
    if (s[0] == 0)
    {
        return;
    }
    
    out[0] = s[0];
    
    prev = code[out[0]];
    for (i = 1; i < 4; i = i + 1)
    {
        if (s[i] == 0)
        {
            break;
        }
        c = code[s[i]];
        if (c == prev)
        {
            continue;
        }
        if (c == -1)
        {
            prev = 0;
        }
        else
        {
            if (c > 0)
            {
                out[i] = c + 48;
                prev = c;
            }
        }
    }
    for (j = i; j < 4; j = j + 1)
    {
        out[j] = 48;
    }
    return;
}
