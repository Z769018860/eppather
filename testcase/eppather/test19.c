int is_leap_year(int a) {
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    int daytab[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };

    leap = is_leap_year(year);

    for (i = 0; yearday > daytab[leap][i]; i = i + 1) {
        yearday = yearday - daytab[leap][i];
    }

    *pmonth = i + 1;
    *pday = yearday;
}
