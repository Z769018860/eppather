void bin(int x[5], int ret[5][32])
{
    int bits[5];
    int i;
    int j;
    int temp[5];
    
    temp[0] = x[0];
    if (temp[0] == 0)
    {
        bits[0] = 1;
    }
    else
    {
        bits[0] = 0;
        for (i = 0; i < 32; i = i + 1)
        {
            if (temp[0] > 0)
            {
                bits[0] = bits[0] + 1;
                temp[0] = temp[0] / 2;
            }
        }
    }
    
    for (i = 0; i < bits[0]; i = i + 1)
    {
        temp[0] = x[0];
        for (j = 0; j < i; j = j + 1)
        {
            temp[0] = temp[0] / 2;
        }
        if (temp[0] % 2 == 1)
        {
            ret[0][bits[0] - i - 1] = 1;
        }
        else
        {
            ret[0][bits[0] - i - 1] = 0;
        }
    }
    
    for (i = bits[0]; i < 32; i = i + 1)
    {
        ret[0][i] = 0;
    }
    
    return;
}
