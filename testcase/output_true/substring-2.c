void substring(int n, int m, int knownCharacter, int knownSubstring[9])
{
    int string[55] = {80,114,111,103,114,97,109,115,32,102,111,114,32,111,116,104,101,114,32,101,110,99,111,100,105,110,103,115,32,40,115,117,99,104,32,97,115,32,56,45,98,105,116,32,65,83,67,73,73,41,46,0};
    int i;
    int j;
    int found;
    
    for (i = n - 1; i < n - 1 + m; i = i + 1)
    {
        if (string[i] == 0)
        {
            break;
        }
    }
    
    for (i = n + 1; string[i] != 0; i = i + 1)
    {
    }
    
    for (i = 0; string[i] != 0; i = i + 1)
    {
    }
    for (j = 0; j < i - 1; j = j + 1)
    {
    }
    
    found = 0;
    for (i = 0; string[i] != 0; i = i + 1)
    {
        if (string[i] == knownCharacter)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        for (j = 0; j < m; j = j + 1)
        {
            if (string[i + j] == 0)
            {
                break;
            }
        }
    }
    
    found = 0;
    for (i = 0; string[i] != 0; i = i + 1)
    {
        int match = 1;
        for (j = 0; knownSubstring[j] != 0; j = j + 1)
        {
            if (string[i + j] != knownSubstring[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        for (j = 0; j < m; j = j + 1)
        {
            if (string[i + j] == 0)
            {
                break;
            }
        }
    }
    
    return;
}
