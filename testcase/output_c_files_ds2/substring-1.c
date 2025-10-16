void putm(char* string, int m)
{
    int i;
    int n1;
    n1 = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (string[n1] != 0 && m > 0)
        {
            m = m - 1;
            n1 = n1 + 1;
        }
    }
    return;
}
