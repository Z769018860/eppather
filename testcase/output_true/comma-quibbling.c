void quib(char strs[5][5], int size, char s[100])
{
    int len = 3;
    int i;
    int j;
    int k;
    
    if (size > 1)
    {
        len = len + 2 * size + 1;
    }
    
    for (i = 0; i < size; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            if (strs[i][j] == 0)
            {
                break;
            }
            len = len + 1;
        }
    }
    
    s[0] = '{';
    s[1] = 0;
    
    if (size == 1)
    {
        for (k = 0; k < 5; k = k + 1)
        {
            if (strs[0][k] == 0)
            {
                break;
            }
            s[k + 1] = strs[0][k];
            s[k + 2] = 0;
        }
    }
    else if (size > 1)
    {
        for (i = 0; i < size - 1; i = i + 1)
        {
            for (k = 0; k < 5; k = k + 1)
            {
                if (strs[i][k] == 0)
                {
                    break;
                }
                s[strlen(s)] = strs[i][k];
            }
            s[strlen(s)] = 0;
            
            if (i < size - 2)
            {
                s[strlen(s)] = ',';
                s[strlen(s) + 1] = ' ';
                s[strlen(s) + 2] = 0;
            }
            else
            {
                s[strlen(s)] = ' ';
                s[strlen(s) + 1] = 'a';
                s[strlen(s) + 2] = 'n';
                s[strlen(s) + 3] = 'd';
                s[strlen(s) + 4] = ' ';
                s[strlen(s) + 5] = 0;
            }
        }
        
        for (k = 0; k < 5; k = k + 1)
        {
            if (strs[i][k] == 0)
            {
                break;
            }
            s[strlen(s)] = strs[i][k];
        }
        s[strlen(s)] = 0;
    }
    
    s[strlen(s)] = '}';
    s[strlen(s) + 1] = 0;
    
    return;
}

int strlen(char s[100])
{
    int i = 0;
    for (i = 0; i < 100; i = i + 1)
    {
        if (s[i] == 0)
        {
            break;
        }
    }
    return i;
}
