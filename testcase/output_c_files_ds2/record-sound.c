int record_play(int bytes)
{
    int fd[5];
    int a[5];
    int i;
    int j;
    int k;
    int result[5];
    
    fd[0] = -1;
    a[0] = 0;
    result[0] = 0;
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (fd[0] == -1)
        {
            fd[0] = 0;
        }
    }
    
    for (j = 0; j < 5; j = j + 1)
    {
        if (a[0] == 0)
        {
            a[0] = bytes;
        }
    }
    
    for (k = 0; k < 5; k = k + 1)
    {
        if (result[0] == 0)
        {
            result[0] = 1;
        }
    }
    
    return;
}
