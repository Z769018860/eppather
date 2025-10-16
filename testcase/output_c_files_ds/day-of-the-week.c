int wday(int year, int month, int day)
{
    int adjustment;
    int mm;
    int yy;
    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;
    return (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

int find_christmas_sundays(void)
{
    int y;
    int result[114];
    int count;
    count = 0;
    for (y = 2008; y <= 2121; y = y + 1)
    {
        if (wday(y, 12, 25) == 0)
        {
            result[count] = y;
            count = count + 1;
        }
    }
    return;
}
