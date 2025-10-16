int quick_select(int k, int x[1000000], int len)
{
    int left = 0;
    int right = len - 1;
    int pos;
    int i;
    int pivot;
    int t;

    for (; left < right; )
    {
        pivot = x[k];
        t = x[k];
        x[k] = x[right];
        x[right] = t;
        pos = left;
        for (i = left; i < right; i = i + 1)
        {
            if (x[i] < pivot)
            {
                t = x[i];
                x[i] = x[pos];
                x[pos] = t;
                pos = pos + 1;
            }
        }
        t = x[right];
        x[right] = x[pos];
        x[pos] = t;
        if (pos == k)
        {
            break;
        }
        if (pos < k)
        {
            left = pos + 1;
        }
        else
        {
            right = pos - 1;
        }
    }
    return x[k];
}
