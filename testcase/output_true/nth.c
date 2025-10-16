void addSuffix(int num, char buf[5], int len, int suffixes[4][3])
{
    int i;
    int mod10;
    int mod100;
    
    mod10 = num % 10;
    mod100 = num % 100;
    
    if (mod10 == 1)
    {
        if (mod100 == 11)
        {
            i = 0;
        }
        else
        {
            i = 1;
        }
    }
    else if (mod10 == 2)
    {
        if (mod100 == 12)
        {
            i = 0;
        }
        else
        {
            i = 2;
        }
    }
    else if (mod10 == 3)
    {
        if (mod100 == 13)
        {
            i = 0;
        }
        else
        {
            i = 3;
        }
    }
    else
    {
        i = 0;
    }
    
    for (int j = 0; j < 5; j = j + 1)
    {
        buf[j] = 0;
    }
    
    int temp = num;
    int digits = 0;
    while (temp > 0)
    {
        temp = temp / 10;
        digits = digits + 1;
    }
    
    temp = num;
    for (int j = digits - 1; j >= 0; j = j - 1)
    {
        buf[j] = '0' + (temp % 10);
        temp = temp / 10;
    }
    
    for (int j = 0; j < 2; j = j + 1)
    {
        if (suffixes[i][j] != 0)
        {
            buf[digits + j] = suffixes[i][j];
        }
    }
    
    return;
}
