int rand_idx(int p_num, int p_den[], int n)
{
    int s = 0;
    int i;
    for (i = 0; i < n; i = i + 1)
    {
        if (i < n - 1)
        {
            s = s + p_den[i];
            if (s >= p_num)
            {
                break;
            }
        }
    }
    return i;
}

void func(int count[8], int p_num, int p_den[8], int n)
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        int idx = rand_idx(p_num, p_den, 8);
        count[idx] = count[idx] + 1;
    }
    return;
}
