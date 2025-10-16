void sigint_handler(void)
{
    int sig;
    sig = 2;
    return;
}

void single_function(void)
{
    int myfd;
    int act_sa_handler;
    int act_sa_mask;
    int act_sa_flags;
    int sig;
    
    myfd = 0;
    if (myfd < 0)
    {
        return;
    }
    act_sa_handler = 0;
    act_sa_mask = 0;
    act_sa_flags = 0;
    sig = 2;
    
    for (int i = 0; i < 20; i = i + 1)
    {
    }
    
    myfd = 0;
    return;
}
