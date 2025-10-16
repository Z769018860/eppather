int F(const int n)
{
    int n1;
    n1 = n;
    if (n1 == 0)
    {
        return 1;
    }
    else
    {
        return n1 - M(F(n1 - 1));
    }
}

int M(const int n)
{
    int n1;
    n1 = n;
    if (n1 == 0)
    {
        return 0;
    }
    else
    {
        return n1 - F(M(n1 - 1));
    }
}

return;
