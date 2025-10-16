void fliprow(int b[4][3], int sz, int n)
{
    int i;
    for(i = 0; i < sz; i = i + 1)
    {
        b[n + 1][i] = !b[n + 1][i];
    }
    return;
}

void flipcol(int b[4][3], int sz, int n)
{
    int i;
    for(i = 1; i <= sz; i = i + 1)
    {
        b[i][n] = !b[i][n];
    }
    return;
}

void initt(int t[4][3], int sz)
{
    int i;
    int j;
    for(i = 1; i <= sz; i = i + 1)
    {
        for(j = 0; j < sz; j = j + 1)
        {
            t[i][j] = (i + j) % 2;
        }
    }
    return;
}

void initb(int t[4][3], int b[4][3], int sz)
{
    int i;
    int j;
    for(i = 1; i <= sz; i = i + 1)
    {
        for(j = 0; j < sz; j = j + 1)
        {
            b[i][j] = t[i][j];
        }
    }
    for(i = 1; i <= sz; i = i + 1)
    {
        fliprow(b, sz, (i * 3 + 1) % sz);
    }
    for(i = 0; i < sz; i = i + 1)
    {
        flipcol(b, sz, (i * 5) % sz);
    }
    return;
}

int eq(int t[4][3], int b[4][3], int sz)
{
    int i;
    int j;
    for(i = 1; i <= sz; i = i + 1)
    {
        for(j = 0; j < sz; j = j + 1)
        {
            if(b[i][j] != t[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void game_logic(int t[4][3], int b[4][3], int sz, char roc, int n)
{
    if(roc == 'r')
    {
        fliprow(b, sz, n);
    }
    else if(roc == 'c')
    {
        flipcol(b, sz, n);
    }
    return;
}
