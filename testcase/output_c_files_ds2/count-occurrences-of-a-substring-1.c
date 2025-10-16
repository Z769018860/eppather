int match(int s[5], int p[5], int overlap)
{
    int c[5];
    int l[5];
    int i[5];
    int j[5];
    int k[5];
    int match[5];
    
    c[0] = 0;
    l[0] = 0;
    while (p[l[0]] != 0)
    {
        l[0] = l[0] + 1;
    }
    
    i[0] = 0;
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        if (s[i[0]] == 0)
        {
            break;
        }
        match[0] = 1;
        for (j[0] = 0; j[0] < l[0]; j[0] = j[0] + 1)
        {
            if (s[i[0] + j[0]] != p[j[0]])
            {
                match[0] = 0;
                break;
            }
        }
        if (match[0] == 1)
        {
            c[0] = c[0] + 1;
            if (overlap == 0)
            {
                i[0] = i[0] + l[0] - 1;
            }
        }
    }
    return c[0];
}
