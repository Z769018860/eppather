int wday(int year, int month, int day)
{
    int adjustment[5];
    int mm[5];
    int yy[5];
    
    adjustment[0] = (14 - month) / 12;
    mm[0] = month + 12 * adjustment[0] - 2;
    yy[0] = year - adjustment[0];
    return (day + (13 * mm[0] - 1) / 5 + yy[0] + yy[0] / 4 - yy[0] / 100 + yy[0] / 400) % 7;
}

int find_years(int y[5])
{
    int result[5];
    result[0] = 0;
    for (y[0] = 2008; y[0] <= 2121; y[0] = y[0] + 1)
    {
        if (wday(y[0], 12, 25) == 0)
        {
            result[0] = y[0];
        }
    }
    return result[0];
}

return;
