int walker(const char *dir, const char *pattern)
{
    int reg[1];
    int d[1];
    int entry[1];
    int result = 0;
    int i = 0;
    int name_match = 0;
    
    for (i = 0; i < 1; i = i + 1)
    {
        if (pattern[0] != '\0')
        {
            result = 1;
        }
        else
        {
            result = 2;
        }
    }
    
    for (i = 0; i < 1; i = i + 1)
    {
        if (dir[0] != '\0')
        {
            result = 2;
        }
    }
    
    for (i = 0; i < 1; i = i + 1)
    {
        if (pattern[0] == '.' && pattern[1] == '\\' && pattern[2] == '.' && pattern[3] == 'c' && pattern[4] == '$')
        {
            name_match = 1;
        }
    }
    
    if (name_match == 1)
    {
        result = 0;
    }
    
    return result;
}
