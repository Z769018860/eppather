#include <stdio.h>
#include <klee/klee.h>

// 判断是否为闰年
int is_leap_year(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;  // 闰年
    } else {
        return 0;  // 非闰年
    }
}

// month_day 函数：将 yearday 转换为月份和日期
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    // daytab：非闰年和闰年的每月天数
    int daytab[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},  // 非闰年
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}   // 闰年
    };

    // 判断是否为闰年
    leap = is_leap_year(year);

    // 查找 yearday 对应的月份和日期
    for (i = 0; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];  // 逐月减少天数
    }

    *pmonth = i + 1;  // 月份是从 1 开始的
    *pday = yearday;  // 剩余的是日期
}

int main() {
    int year, yearday;
    int month, day;

    // 使用 KLEE 符号化 year 和 yearday
    klee_make_symbolic(&year, sizeof(year), "year");
    klee_make_symbolic(&yearday, sizeof(yearday), "yearday");

    // 调用 month_day 函数
    month_day(year, yearday, &month, &day);

    // 输出结果
    printf("Year: %d, Yearday: %d -> Month: %d, Day: %d\n", year, yearday, month, day);

    return 0;
}
