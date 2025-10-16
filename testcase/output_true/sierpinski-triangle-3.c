void sierpinski_triangle(int n)
{
    int i;
    int j;
    int l[5];
    l[0] = 1;
    for (i = 0; i < n + 1; i = i + 1)
    {
        l[0] = l[0] * 2;
    }
    char b[5][1024];
    for (i = 0; i < l[0]; i = i + 1)
    {
        b[0][i] = ' ';
    }
    b[0][l[0]] = '\0';
    b[0][l[0] / 2] = '*';
    for (i = 0; i < l[0] / 2 - 1; i = i + 1)
    {
        for (j = 1; j < l[0] - 1; j = j + 1)
        {
            if ((b[0][j - 1] == '*' && b[0][j + 1] == ' ') || (b[0][j - 1] == ' ' && b[0][j + 1] == '*'))
            {
                b[1][j] = '*';
            }
            else
            {
                b[1][j] = ' ';
            }
        }
        for (j = 1; j < l[0] - 1; j = j + 1)
        {
            b[0][j] = b[1][j];
        }
    }
    return;
}
