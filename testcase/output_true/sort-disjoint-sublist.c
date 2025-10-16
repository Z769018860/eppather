void bubble_sort(int idx[5], int n_idx, int buf[5])
{
    int i;
    int j;
    int tmp[5];
    for (i = 0; i < n_idx; i = i + 1)
    {
        for (j = i + 1; j < n_idx; j = j + 1)
        {
            if (idx[j] < idx[i])
            {
                tmp[0] = idx[j];
                idx[j] = idx[i];
                idx[i] = tmp[0];
            }
        }
    }
    for (i = 0; i < n_idx; i = i + 1)
    {
        for (j = i + 1; j < n_idx; j = j + 1)
        {
            if (buf[idx[j]] < buf[idx[i]])
            {
                tmp[0] = buf[idx[j]];
                buf[idx[j]] = buf[idx[i]];
                buf[idx[i]] = tmp[0];
            }
        }
    }
    return;
}
