int depth(int in[5], int d)
{
    int r_depth[5] = {0};
    int r_p[10][5] = {0};
    int i = 0;
    int s = 0;
    int c[10] = {0};
    int number[100][4] = {0};
    int buf[5] = {0};
    int temp = 0;

    for (i = 0; i < 5; i = i + 1)
    {
        buf[i] = in[i];
    }

    if (r_depth[0] > 0)
    {
        return r_depth[0];
    }

    d = d + 1;
    if (r_depth[0] == 0)
    {
        r_depth[0] = -d;
    }
    else
    {
        r_depth[0] = r_depth[0] + d;
    }

    for (s = 0; buf[s] != 0; s = s + 1)
    {
        c[buf[s] - 48] = c[buf[s] - 48] + 1;
    }

    for (i = 9; i >= 0; i = i - 1)
    {
        if (c[i] == 0)
        {
            continue;
        }
        temp = c[i];
        if (temp < 10)
        {
            buf[0] = temp + 48;
            buf[1] = i + 48;
            buf[2] = 0;
        }
        else
        {
            buf[0] = (temp / 10) + 48;
            buf[1] = (temp % 10) + 48;
            buf[2] = i + 48;
            buf[3] = 0;
        }
    }

    d = depth(buf, d);

    if (r_depth[0] <= 0)
    {
        r_depth[0] = d + 1;
    }
    return r_depth[0];
}
