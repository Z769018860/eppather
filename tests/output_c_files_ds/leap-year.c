int is_leap_year(int year)
{
    int result;
    if ((year % 4) == 0)
    {
        if ((year % 100) != 0)
        {
            result = 1;
        }
        else
        {
            if ((year % 400) == 0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    else
    {
        result = 0;
    }
    return result;
}
