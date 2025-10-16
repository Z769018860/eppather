int F(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        int temp[5];
        temp[0] = F(n - 1);
        return n - M(temp[0]);
    }
}

int M(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        int temp[5];
        temp[0] = M(n - 1);
        return n - F(temp[0]);
    }
}

int main()
{
    return;
}
