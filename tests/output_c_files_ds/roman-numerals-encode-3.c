int to_roman(char *out, int n)
{
    int len = 0;
    if (n <= 0)
    {
        return 0;
    }
    for (; n >= 1000; n = n - 1000)
    {
        if (out)
        {
            out[len] = 'M';
        }
        len = len + 1;
    }
    if (n >= 900)
    {
        n = n - 900;
        if (out)
        {
            out[len] = 'C';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'M';
        }
        len = len + 1;
    }
    if (n >= 500)
    {
        n = n - 500;
        if (out)
        {
            out[len] = 'D';
        }
        len = len + 1;
    }
    if (n >= 400)
    {
        n = n - 400;
        if (out)
        {
            out[len] = 'C';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'D';
        }
        len = len + 1;
    }
    for (; n >= 100; n = n - 100)
    {
        if (out)
        {
            out[len] = 'C';
        }
        len = len + 1;
    }
    if (n >= 90)
    {
        n = n - 90;
        if (out)
        {
            out[len] = 'X';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'C';
        }
        len = len + 1;
    }
    if (n >= 50)
    {
        n = n - 50;
        if (out)
        {
            out[len] = 'L';
        }
        len = len + 1;
    }
    if (n >= 40)
    {
        n = n - 40;
        if (out)
        {
            out[len] = 'X';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'L';
        }
        len = len + 1;
    }
    for (; n >= 10; n = n - 10)
    {
        if (out)
        {
            out[len] = 'X';
        }
        len = len + 1;
    }
    if (n >= 9)
    {
        n = n - 9;
        if (out)
        {
            out[len] = 'I';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'X';
        }
        len = len + 1;
    }
    if (n >= 5)
    {
        n = n - 5;
        if (out)
        {
            out[len] = 'V';
        }
        len = len + 1;
    }
    if (n >= 4)
    {
        n = n - 4;
        if (out)
        {
            out[len] = 'I';
        }
        len = len + 1;
        if (out)
        {
            out[len] = 'V';
        }
        len = len + 1;
    }
    for (; n > 0; n = n - 1)
    {
        if (out)
        {
            out[len] = 'I';
        }
        len = len + 1;
    }
    if (out)
    {
        out[len] = '\0';
    }
    len = len + 1;
    return len;
}
