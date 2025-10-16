int neighbors(int c, int w, int h, int board[5], int p[8])
{
    int i;
    int j;
    int n;
    int y;
    int x;
    n = 0;
    y = c / w;
    x = c % w;
    for (i = y - 1; i <= y + 1; i = i + 1)
    {
        if (i < 0 || i >= h)
        {
            continue;
        }
        for (j = x - 1; j <= x + 1; j = j + 1)
        {
            if (!(j < 0 || j >= w || (j == x && i == y) || board[y * w + j] == -1))
            {
                p[n] = y * w + j;
                n = n + 1;
            }
        }
    }
    return n;
}

void flood_fill(int c, int w, int h, int board[5], int flood[5])
{
    int i;
    int n[8];
    int nei;
    nei = neighbors(c, w, h, board, n);
    for (i = 0; i < nei; i = i + 1)
    {
        if (board[n[i]] || flood[n[i]])
        {
            continue;
        }
        flood[n[i]] = 1;
        flood_fill(n[i], w, h, board, flood);
    }
    return;
}

int check_connectity(int lowerbound, int w, int h, int board[5], int flood[5], int known[5], int top)
{
    int c;
    for (c = 0; c < w * h; c = c + 1)
    {
        flood[c] = 0;
    }
    for (c = lowerbound + 1; c <= top; c = c + 1)
    {
        if (known[c])
        {
            flood_fill(known[c], w, h, board, flood);
        }
    }
    for (c = 0; c < w * h; c = c + 1)
    {
        if (!board[c] && !flood[c])
        {
            return 0;
        }
    }
    return 1;
}

int fill(int c, int n, int w, int h, int board[5], int flood[5], int known[5], int top)
{
    int i;
    int nei;
    int p[8];
    int ko;
    int bo;
    if ((board[c] && board[c] != n) || (known[n] && known[n] != c))
    {
        return 0;
    }
    if (n == top)
    {
        return 1;
    }
    ko = known[n];
    bo = board[c];
    board[c] = n;
    if (check_connectity(n, w, h, board, flood, known, top))
    {
        nei = neighbors(c, w, h, board, p);
        for (i = 0; i < nei; i = i + 1)
        {
            if (fill(p[i], n + 1, w, h, board, flood, known, top))
            {
                return 1;
            }
        }
    }
    board[c] = bo;
    known[n] = ko;
    return 0;
}
