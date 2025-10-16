int fill(int cells[5], int end[5], int p[5], int m[5])
{
    if ((p[0] & 1))
    {
        return 0;
    }
    p[0] = p[0] | 1;
    if (p[0] >= end[0])
    {
        return 1;
    }
    if (!(p[0] & 4) && fill(cells, end, p + m[0], m))
    {
        return 1;
    }
    if (!(p[0] & 2) && fill(cells, end, p + 1, m))
    {
        return 1;
    }
    if (!(p[-1] & 2) && fill(cells, end, p - 1, m))
    {
        return 1;
    }
    if (!(p[-m[0]] & 4) && fill(cells, end, p - m[0], m))
    {
        return 1;
    }
    return 0;
}

int percolate(int cells[5], int end[5], int m[5])
{
    int i;
    for (i = 0; i < m[0]; i = i + 1)
    {
        if (fill(cells, end, cells + i, m))
        {
            break;
        }
    }
    return i < m[0];
}

void make_grid(int cells[5], int start[5], int end[5], int m[5], int n[5], int thresh[5], int x[5], int y[5])
{
    int i;
    int j;
    for (i = 0; i < m[0]; i = i + 1)
    {
        start[i] = 4 | 2;
    }
    for (i = 0; i < y[0]; i = i + 1)
    {
        for (j = x[0]; j > 0; j = j - 1)
        {
            end[0] = ((rand() < thresh[0] ? 4 : 0) | (rand() < thresh[0] ? 2 : 0));
            end[0] = end[0] + 1;
        }
        end[0] = 2 | (rand() < thresh[0] ? 4 : 0);
        end[0] = end[0] + 1;
    }
    for (i = 0; i < m[0]; i = i + 1)
    {
        end[i] = 0;
    }
    return;
}

void show_grid(int cells[5], int m[5], int n[5])
{
    int i;
    int j;
    for (j = 0; j < m[0]; j = j + 1)
    {
    }
    for (i = 0; i <= n[0]; i = i + 1)
    {
        for (j = 0; j < m[0]; j = j + 1)
        {
            if (cells[i * m[0] + j] & 1)
            {
            }
            if (cells[i * m[0] + j] & 2)
            {
            }
        }
        if (i == n[0])
        {
            return;
        }
        for (j = 0; j < m[0]; j = j + 1)
        {
            if (cells[i * m[0] + j] & 4)
            {
            }
        }
    }
    return;
}
