void substring_operations(int n, int m, int knownCharacter, int knownSubstring[9], int string[50])
{
    int i;
    int j;
    int k;
    int found;
    int temp[50];
    
    for (i = 0; i < 50; i = i + 1)
    {
        temp[i] = string[i];
    }
    
    for (i = n - 1; i < n - 1 + m; i = i + 1)
    {
        if (temp[i] == 0)
        {
            break;
        }
    }
    
    for (i = n + 1; i < 50; i = i + 1)
    {
        if (temp[i] == 0)
        {
            break;
        }
    }
    
    for (i = 0; i < 49; i = i + 1)
    {
        if (temp[i] == 0)
        {
            break;
        }
    }
    
    found = 0;
    for (i = 0; i < 50; i = i + 1)
    {
        if (temp[i] == knownCharacter)
        {
            found = 1;
            for (j = i; j < i + m; j = j + 1)
            {
                if (temp[j] == 0)
                {
                    break;
                }
            }
            break;
        }
    }
    
    found = 0;
    for (i = 0; i < 42; i = i + 1)
    {
        for (j = 0; j < 9; j = j + 1)
        {
            if (temp[i + j] != knownSubstring[j])
            {
                break;
            }
        }
        if (j == 9)
        {
            found = 1;
            for (k = i; k < i + m; k = k + 1)
            {
                if (temp[k] == 0)
                {
                    break;
                }
            }
            break;
        }
    }
    
    return;
}
