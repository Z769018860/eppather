int pancake_sort(int list[5], int length)
{
    int i;
    int a;
    int max_num_pos;
    int moves;
    moves = 0;
    
    if (length < 2)
    {
        return 0;
    }
    
    for (i = length; i > 1; i = i - 1)
    {
        max_num_pos = 0;
        for (a = 0; a < i; a = a + 1)
        {
            if (list[a] > list[max_num_pos])
            {
                max_num_pos = a;
            }
        }
        
        if (max_num_pos == i - 1)
        {
            continue;
        }
        
        if (max_num_pos != 0)
        {
            moves = moves + 1;
            int temp;
            int start;
            int end;
            start = 0;
            end = max_num_pos;
            while (start < end)
            {
                temp = list[start];
                list[start] = list[end];
                list[end] = temp;
                start = start + 1;
                end = end - 1;
            }
        }
        
        moves = moves + 1;
        {
            int temp;
            int start;
            int end;
            start = 0;
            end = i - 1;
            while (start < end)
            {
                temp = list[start];
                list[start] = list[end];
                list[end] = temp;
                start = start + 1;
                end = end - 1;
            }
        }
    }
    
    return moves;
}
