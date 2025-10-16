int rand_idx(int p[8], int n, int rand_val)
{
    int s = rand_val;
    int i;
    for (i = 0; i < n - 1; i = i + 1)
    {
        s = s - p[i];
        if (s < 0)
        {
            break;
        }
    }
    return i;
}
