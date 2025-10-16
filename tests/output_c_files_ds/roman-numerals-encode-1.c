void roman(char *s, unsigned int n)
{
    if (n == 0)
    {
        return;
    }

    for (; n >= 1000; n = n - 1000)
    {
        *s = 'M';
        s = s + 1;
    }
    if (n >= 900)
    {
        *s = 'C';
        s = s + 1;
        *s = 'M';
        s = s + 1;
        n = n - 900;
    }
    if (n >= 500)
    {
        *s = 'D';
        s = s + 1;
        n = n - 500;
    }
    if (n >= 400)
    {
        *s = 'C';
        s = s + 1;
        *s = 'D';
        s = s + 1;
        n = n - 400;
    }
    for (; n >= 100; n = n - 100)
    {
        *s = 'C';
        s = s + 1;
    }
    if (n >= 90)
    {
        *s = 'X';
        s = s + 1;
        *s = 'C';
        s = s + 1;
        n = n - 90;
    }
    if (n >= 50)
    {
        *s = 'L';
        s = s + 1;
        n = n - 50;
    }
    if (n >= 40)
    {
        *s = 'X';
        s = s + 1;
        *s = 'L';
        s = s + 1;
        n = n - 40;
    }
    for (; n >= 10; n = n - 10)
    {
        *s = 'X';
        s = s + 1;
    }
    if (n >= 9)
    {
        *s = 'I';
        s = s + 1;
        *s = 'X';
        s = s + 1;
        n = n - 9;
    }
    if (n >= 5)
    {
        *s = 'V';
        s = s + 1;
        n = n - 5;
    }
    if (n >= 4)
    {
        *s = 'I';
        s = s + 1;
        *s = 'V';
        s = s + 1;
        n = n - 4;
    }
    for (; n >= 1; n = n - 1)
    {
        *s = 'I';
        s = s + 1;
    }
    *s = '\0';
    return;
}
