void show_sym_diff(const char *const x[5], int lenx, const char *const y[5], int leny)
{
    int i;
    int j;
    int found;
    for (i = 0; i < lenx; i = i + 1)
    {
        if (x[i])
        {
            found = 0;
            for (j = 0; j < leny; j = j + 1)
            {
                if (y[j])
                {
                    int k = 0;
                    while (x[i][k] && y[j][k] && x[i][k] == y[j][k])
                    {
                        k = k + 1;
                    }
                    if (x[i][k] == 0 && y[j][k] == 0)
                    {
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 0)
            {
            }
        }
    }
    for (i = 0; i < leny; i = i + 1)
    {
        if (y[i])
        {
            found = 0;
            for (j = 0; j < lenx; j = j + 1)
            {
                if (x[j])
                {
                    int k = 0;
                    while (y[i][k] && x[j][k] && y[i][k] == x[j][k])
                    {
                        k = k + 1;
                    }
                    if (y[i][k] == 0 && x[j][k] == 0)
                    {
                        found = 1;
                        break;
                    }
                }
            }
            if (found == 0)
            {
            }
        }
    }
    return;
}
