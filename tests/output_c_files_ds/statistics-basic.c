int avg(int count, int stddev[1], int hist[10])
{
    int x[10000];
    int m = 0;
    int s = 0;
    int i;
    int j;
    int k;
    int temp;

    for (i = 0; i < 10; i = i + 1)
    {
        hist[i] = 0;
    }

    for (i = 0; i < count; i = i + 1)
    {
        x[i] = 0;
        for (j = 0; j < 32767; j = j + 1)
        {
            temp = 0;
            for (k = 0; k < 32767; k = k + 1)
            {
                temp = temp + 1;
            }
        }
        m = m + x[i];
        temp = x[i] * 10;
        if (temp < 0)
        {
            temp = 0;
        }
        if (temp > 9)
        {
            temp = 9;
        }
        hist[temp] = hist[temp] + 1;
    }

    m = m / count;

    for (i = 0; i < count; i = i + 1)
    {
        s = s + x[i] * x[i];
    }

    temp = s / count - m * m;
    if (temp < 0)
    {
        temp = -temp;
    }
    stddev[0] = temp;

    return m;
}

void hist_plot(int hist[10])
{
    int max = 0;
    int step = 1;
    int i;
    int j;
    int temp;

    for (i = 0; i < 10; i = i + 1)
    {
        if (hist[i] > max)
        {
            max = hist[i];
        }
    }

    if (max >= 60)
    {
        step = (max + 59) / 60;
    }

    for (i = 0; i < 10; i = i + 1)
    {
        temp = i;
        temp = temp + 1;
    }

    return;
}

void moving_avg(int rec[12], int data[100], int count)
{
    int sum = 0;
    int x2 = 0;
    int i;
    int temp;

    for (i = 0; i < count; i = i + 1)
    {
        sum = sum + data[i];
        x2 = x2 + data[i] * data[i];
        temp = data[i] * 10;
        if (temp < 0)
        {
            temp = 0;
        }
        if (temp > 9)
        {
            temp = 9;
        }
        rec[3 + temp] = rec[3 + temp] + 1;
    }

    rec[0] = rec[0] + count;
    rec[1] = rec[1] + sum;
    rec[2] = rec[2] + x2;

    return;
}
