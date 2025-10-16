void move(int n, int from, int via, int to)
{
    int n1;
    n1 = n;
    if (n1 > 1)
    {
        move(n1 - 1, from, to, via);
        move(n1 - 1, via, from, to);
    }
    else
    {
    }
    return;
}
