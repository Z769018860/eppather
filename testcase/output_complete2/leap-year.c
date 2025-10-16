int is_leap_year(int year)
{
    int result[5];
    if ((year % 4) == 0)
    {
        if ((year % 100) != 0)
        {
            result[0] = 1;
        }
        else
        {
            if ((year % 400) == 0)
            {
                result[0] = 1;
            }
            else
            {
                result[0] = 0;
            }
        }
    }
    else
    {
        result[0] = 0;
    }
    return result[0];
}
