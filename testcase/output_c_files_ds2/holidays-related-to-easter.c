int easter_related(int year, int holidays[5][3])
{
    int date[3];
    int c;
    int n;
    int i;
    int l;
    int days[13];
    days[0] = 0;
    days[1] = 31;
    days[2] = 28;
    days[3] = 31;
    days[4] = 30;
    days[5] = 31;
    days[6] = 30;
    days[7] = 31;
    days[8] = 31;
    days[9] = 30;
    days[10] = 31;
    days[11] = 30;
    days[12] = 31;
    
    date[0] = year;
    c = year / 100;
    n = year % 19;
    i = (c - c / 4 - (c - (c - 17) / 25) / 3 + 19 * n + 15) % 30;
    i = i - (i / 28) * (1 - (i / 28) * (29 / (i + 1)) * ((21 - n) / 11));
    l = i - (year + year / 4 + i + 2 - c + c / 4) % 7;
    date[1] = 3 + (l + 40) / 44;
    date[2] = l + 28 - 31 * (date[1] / 4);
    holidays[0][0] = date[0];
    holidays[0][1] = date[1];
    holidays[0][2] = date[2];
    
    for (int j = 0; j < 39; j = j + 1)
    {
        date[2] = date[2] + 1;
        if (date[2] > ((date[1] == 2) ? 28 + ((date[0] % 4 == 0 && date[0] % 100 != 0) || date[0] % 400 == 0) : days[date[1]]))
        {
            date[2] = 1;
            date[1] = date[1] + 1;
            if (date[1] > 12)
            {
                date[1] = 1;
                date[0] = date[0] + 1;
            }
        }
    }
    holidays[1][0] = date[0];
    holidays[1][1] = date[1];
    holidays[1][2] = date[2];
    
    for (int j = 0; j < 10; j = j + 1)
    {
        date[2] = date[2] + 1;
        if (date[2] > ((date[1] == 2) ? 28 + ((date[0] % 4 == 0 && date[0] % 100 != 0) || date[0] % 400 == 0) : days[date[1]]))
        {
            date[2] = 1;
            date[1] = date[1] + 1;
            if (date[1] > 12)
            {
                date[1] = 1;
                date[0] = date[0] + 1;
            }
        }
    }
    holidays[2][0] = date[0];
    holidays[2][1] = date[1];
    holidays[2][2] = date[2];
    
    for (int j = 0; j < 7; j = j + 1)
    {
        date[2] = date[2] + 1;
        if (date[2] > ((date[1] == 2) ? 28 + ((date[0] % 4 == 0 && date[0] % 100 != 0) || date[0] % 400 == 0) : days[date[1]]))
        {
            date[2] = 1;
            date[1] = date[1] + 1;
            if (date[1] > 12)
            {
                date[1] = 1;
                date[0] = date[0] + 1;
            }
        }
    }
    holidays[3][0] = date[0];
    holidays[3][1] = date[1];
    holidays[3][2] = date[2];
    
    for (int j = 0; j < 4; j = j + 1)
    {
        date[2] = date[2] + 1;
        if (date[2] > ((date[1] == 2) ? 28 + ((date[0] % 4 == 0 && date[0] % 100 != 0) || date[0] % 400 == 0) : days[date[1]]))
        {
            date[2] = 1;
            date[1] = date[1] + 1;
            if (date[1] > 12)
            {
                date[1] = 1;
                date[0] = date[0] + 1;
            }
        }
    }
    holidays[4][0] = date[0];
    holidays[4][1] = date[1];
    holidays[4][2] = date[2];
    
    return;
}
