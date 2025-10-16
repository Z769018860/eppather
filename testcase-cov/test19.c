void month_day(int year,int yearday,int *pmonth,int *pday)
{
    int i,leap;
    int daytab[10][10];
    leap=is_leap_year(year);
    for (i=1;yearday>daytab[leap][i];i=i+1)
        yearday=yearday-daytab[leap][i];
    *pmonth=i;
    *pday=yearday;
}