int check_month(int y, int m)
{
    int days[31];
    int i;
    int j;
    int valid;
    int weekday;
    int day;
    int count;
    
    valid = 1;
    if (m < 1 || m > 12)
    {
        valid = 0;
    }
    else
    {
        if (m == 2)
        {
            if ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0))
            {
                day = 29;
            }
            else
            {
                day = 28;
            }
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            day = 30;
        }
        else
        {
            day = 31;
        }
        
        weekday = (y + (y / 4) - (y / 100) + (y / 400) + (13 * (m + 1) / 5) + 1) % 7;
        for (i = 0; i < day; i = i + 1)
        {
            days[i] = (weekday + i) % 7;
        }
        
        count = 0;
        for (i = 0; i < day; i = i + 1)
        {
            if (days[i] == 5)
            {
                count = count + 1;
            }
        }
        if (count != 5)
        {
            valid = 0;
        }
        
        count = 0;
        for (i = 0; i < day; i = i + 1)
        {
            if (days[i] == 6)
            {
                count = count + 1;
            }
        }
        if (count != 5)
        {
            valid = 0;
        }
        
        count = 0;
        for (i = 0; i < day; i = i + 1)
        {
            if (days[i] == 0)
            {
                count = count + 1;
            }
        }
        if (count != 5)
        {
            valid = 0;
        }
    }
    
    return valid;
}
