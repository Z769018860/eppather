int easter_related_init(int year, int result[5][4])
{
    int c;
    int n;
    int i;
    int l;
    int date[4];
    int temp[4];
    int days;
    int month_days[13];
    int year_days;
    int year_months;
    int week_days;
    int is_leap;
    
    month_days[0] = 0;
    month_days[1] = 31;
    month_days[2] = 28;
    month_days[3] = 31;
    month_days[4] = 30;
    month_days[5] = 31;
    month_days[6] = 30;
    month_days[7] = 31;
    month_days[8] = 31;
    month_days[9] = 30;
    month_days[10] = 31;
    month_days[11] = 30;
    month_days[12] = 31;
    year_months = 12;
    week_days = 7;
    
    is_leap = 0;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        is_leap = 1;
    }
    if (is_leap)
    {
        month_days[2] = 29;
    }
    year_days = 365 + is_leap;
    
    c = year / 100;
    n = year % 19;
    i = (c - c / 4 - (c - (c - 17) / 25) / 3 + 19 * n + 15) % 30;
    i = i - (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));
    l = i - (year + year / 4 + i + 2 - c + c / 4) % 7;
    date[0] = year;
    date[1] = 3 + (l + 40) / 44;
    date[2] = l + 28 - 31 * (date[1] / 4);
    
    temp[0] = date[0];
    temp[1] = date[1];
    temp[2] = date[2];
    if (temp[1] <= 2)
    {
        temp[1] = temp[1] + 12;
        temp[0] = temp[0] - 1;
    }
    c = temp[0] / 100;
    temp[0] = temp[0] % 100;
    date[3] = 1 + ((temp[2] + ((temp[1] + 1) * 26) / 10 + temp[0] + temp[0] / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    
    result[0][0] = date[0];
    result[0][1] = date[1];
    result[0][2] = date[2];
    result[0][3] = date[3];
    
    days = 39;
    temp[0] = date[0];
    temp[1] = date[1];
    temp[2] = date[2] + days;
    for (; temp[2] > month_days[temp[1]]; )
    {
        temp[2] = temp[2] - month_days[temp[1]];
        temp[1] = temp[1] + 1;
        if (temp[1] > year_months)
        {
            temp[1] = temp[1] - year_months;
            temp[0] = temp[0] + 1;
            is_leap = 0;
            if ((temp[0] % 4 == 0 && temp[0] % 100 != 0) || temp[0] % 400 == 0)
            {
                is_leap = 1;
            }
            month_days[2] = 28 + is_leap;
        }
    }
    if (temp[1] <= 2)
    {
        c = (temp[0] - 1) / 100;
        l = (temp[0] - 1) % 100;
    }
    else
    {
        c = temp[0] / 100;
        l = temp[0] % 100;
    }
    temp[3] = 1 + ((temp[2] + ((temp[1] + 1) * 26) / 10 + l + l / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    result[1][0] = temp[0];
    result[1][1] = temp[1];
    result[1][2] = temp[2];
    result[1][3] = temp[3];
    
    days = 10;
    temp[2] = temp[2] + days;
    for (; temp[2] > month_days[temp[1]]; )
    {
        temp[2] = temp[2] - month_days[temp[1]];
        temp[1] = temp[1] + 1;
        if (temp[1] > year_months)
        {
            temp[1] = temp[1] - year_months;
            temp[0] = temp[0] + 1;
            is_leap = 0;
            if ((temp[0] % 4 == 0 && temp[0] % 100 != 0) || temp[0] % 400 == 0)
            {
                is_leap = 1;
            }
            month_days[2] = 28 + is_leap;
        }
    }
    if (temp[1] <= 2)
    {
        c = (temp[0] - 1) / 100;
        l = (temp[0] - 1) % 100;
    }
    else
    {
        c = temp[0] / 100;
        l = temp[0] % 100;
    }
    temp[3] = 1 + ((temp[2] + ((temp[1] + 1) * 26) / 10 + l + l / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    result[2][0] = temp[0];
    result[2][1] = temp[1];
    result[2][2] = temp[2];
    result[2][3] = temp[3];
    
    days = 7;
    temp[2] = temp[2] + days;
    for (; temp[2] > month_days[temp[1]]; )
    {
        temp[2] = temp[2] - month_days[temp[1]];
        temp[1] = temp[1] + 1;
        if (temp[1] > year_months)
        {
            temp[1] = temp[1] - year_months;
            temp[0] = temp[0] + 1;
            is_leap = 0;
            if ((temp[0] % 4 == 0 && temp[0] % 100 != 0) || temp[0] % 400 == 0)
            {
                is_leap = 1;
            }
            month_days[2] = 28 + is_leap;
        }
    }
    if (temp[1] <= 2)
    {
        c = (temp[0] - 1) / 100;
        l = (temp[0] - 1) % 100;
    }
    else
    {
        c = temp[0] / 100;
        l = temp[0] % 100;
    }
    temp[3] = 1 + ((temp[2] + ((temp[1] + 1) * 26) / 10 + l + l / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    result[3][0] = temp[0];
    result[3][1] = temp[1];
    result[3][2] = temp[2];
    result[3][3] = temp[3];
    
    days = 4;
    temp[2] = temp[2] + days;
    for (; temp[2] > month_days[temp[1]]; )
    {
        temp[2] = temp[2] - month_days[temp[1]];
        temp[1] = temp[1] + 1;
        if (temp[1] > year_months)
        {
            temp[1] = temp[1] - year_months;
            temp[0] = temp[0] + 1;
            is_leap = 0;
            if ((temp[0] % 4 == 0 && temp[0] % 100 != 0) || temp[0] % 400 == 0)
            {
                is_leap = 1;
            }
            month_days[2] = 28 + is_leap;
        }
    }
    if (temp[1] <= 2)
    {
        c = (temp[0] - 1) / 100;
        l = (temp[0] - 1) % 100;
    }
    else
    {
        c = temp[0] / 100;
        l = temp[0] % 100;
    }
    temp[3] = 1 + ((temp[2] + ((temp[1] + 1) * 26) / 10 + l + l / 4 + c / 4 - 2 * c) % 7 + 7) % 7;
    result[4][0] = temp[0];
    result[4][1] = temp[1];
    result[4][2] = temp[2];
    result[4][3] = temp[3];
    
    return;
}
