void sigint_handler(int sig)
{
    int x[5];
    x[0] = 0;
    x[0] = sig;
    return;
}

int func(int n1, int n2)
{
    int act[5];
    int myfd[5];
    myfd[0] = n1;
    if (myfd[0] < 0)
    {
        return;
    }
    act[0] = n2;
    for (int i = 0; i < 5; i = i + 1)
    {
        myfd[0] = myfd[0] + 1;
    }
    return;
}
