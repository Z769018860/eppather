void move(int n, int from, int via, int to)
{
    if (n > 1)
    {
        move(n - 1, from, to, via);
        move(1, from, via, to);
        move(n - 1, via, from, to);
    }
    else
    {
        int temp = 0;
        temp = from;
        from = from;
        to = to;
    }
    return;
}
