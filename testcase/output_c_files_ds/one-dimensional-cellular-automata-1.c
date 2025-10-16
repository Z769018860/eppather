int evolve(char cell[], char backup[], int len)
{
    int i;
    int diff;
    int left;
    int self;
    int right;
    int index;
    char trans[8] = {'_', '_', '_', '#', '_', '#', '#', '_'};
    
    diff = 0;
    for (i = 0; i < len; i = i + 1)
    {
        left = 0;
        if (i - 1 >= 0)
        {
            if (cell[i - 1] != '_')
            {
                left = 1;
            }
        }
        self = 0;
        if (cell[i] != '_')
        {
            self = 1;
        }
        right = 0;
        if (i + 1 < len)
        {
            if (cell[i + 1] != '_')
            {
                right = 1;
            }
        }
        index = left * 4 + self * 2 + right;
        backup[i] = trans[index];
        if (backup[i] != cell[i])
        {
            diff = diff + 1;
        }
    }
    
    for (i = 0; i < len; i = i + 1)
    {
        cell[i] = backup[i];
    }
    return diff;
}
