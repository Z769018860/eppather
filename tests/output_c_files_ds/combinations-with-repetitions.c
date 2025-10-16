int choose(int* got, int n_chosen, int len, int at, int max_types)
{
    int i;
    int count;
    count = 0;
    if (n_chosen == len)
    {
        if (got == 0)
        {
            return 1;
        }
        for (i = 0; i < len; i = i + 1)
        {
        }
        return 1;
    }
    for (i = at; i < max_types; i = i + 1)
    {
        if (got != 0)
        {
            got[n_chosen] = i;
        }
        count = count + choose(got, n_chosen + 1, len, i, max_types);
    }
    return count;
}
