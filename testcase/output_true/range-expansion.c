int get_list(const char *s, char **e)
{
    int x[5];
    int y[5];
    int ee[5];
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        x[i] = 0;
        y[i] = 0;
        ee[i] = 0;
    }
    while (1)
    {
        for (i = 0; i < 5; i = i + 1)
        {
            if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
            {
                s = s + 1;
            }
            else
            {
                break;
            }
        }
        if (get_rnge(s, e) == 0)
        {
            x[0] = 0;
            for (i = 0; i < 5; i = i + 1)
            {
                if (s[i] >= '0' && s[i] <= '9')
                {
                    x[0] = x[0] * 10 + (s[i] - '0');
                }
                else
                {
                    break;
                }
            }
            if (i == 0)
            {
                break;
            }
            *e = (char *)(s + i);
        }
        s = *e;
        for (i = 0; i < 5; i = i + 1)
        {
            if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
            {
                s = s + 1;
            }
            else
            {
                break;
            }
        }
        if ((*s) == '\0')
        {
            return 1;
        }
        if ((*s) == ',')
        {
            s = s + 1;
            continue;
        }
        break;
    }
    *e = (char *)s;
    return 0;
}

int get_rnge(const char *s, char **e)
{
    int x[5];
    int y[5];
    char *ee[5];
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        x[i] = 0;
        y[i] = 0;
        ee[i] = 0;
    }
    x[0] = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            x[0] = x[0] * 10 + (s[i] - '0');
        }
        else
        {
            break;
        }
    }
    if (i == 0)
    {
        return 0;
    }
    ee[0] = (char *)(s + i);
    s = ee[0];
    for (i = 0; i < 5; i = i + 1)
    {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
        {
            s = s + 1;
        }
        else
        {
            break;
        }
    }
    if (*s != '-')
    {
        *e = (char *)s;
        return 0;
    }
    s = s + 1;
    y[0] = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            y[0] = y[0] * 10 + (s[i] - '0');
        }
        else
        {
            break;
        }
    }
    if (i == 0)
    {
        return 0;
    }
    *e = (char *)(s + i);
    if (y[0] <= x[0])
    {
        return 0;
    }
    for (i = x[0]; i <= y[0]; i = i + 1)
    {
    }
    return 1;
}

void add_number(int x[5])
{
}

int add_range(int x[5], int y[5])
{
    if (y[0] <= x[0])
    {
        return 0;
    }
    for (x[0] = x[0]; x[0] <= y[0]; x[0] = x[0] + 1)
    {
    }
    return 1;
}

void main()
{
    return;
}
