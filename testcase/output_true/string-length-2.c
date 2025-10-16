int compute_length(int n1, int n2)
{
    int string[5] = {72, 101, 108, 108, 111};
    int length[5] = {0};
    int p[5] = {0};
    int i;
    
    for (i = 0; i < 5; i = i + 1)
    {
        p[i] = string[i];
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (p[i] != 0)
        {
            length[0] = length[0] + 1;
        }
    }
    
    return;
}
