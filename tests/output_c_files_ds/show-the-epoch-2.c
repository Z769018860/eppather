int func() {
    int ft_dwLowDateTime = 0;
    int ft_dwHighDateTime = 0;
    int st_wYear = 0;
    int st_wMonth = 0;
    int st_wDayOfWeek = 0;
    int st_wDay = 0;
    int st_wHour = 0;
    int st_wMinute = 0;
    int st_wSecond = 0;
    int st_wMilliseconds = 0;
    int date[80] = {0};
    int time[80] = {0};
    int result = 0;

    for (int i = 0; i < 80; i = i + 1) {
        date[i] = 0;
        time[i] = 0;
    }

    st_wYear = 1601;
    st_wMonth = 1;
    st_wDay = 1;
    st_wHour = 0;
    st_wMinute = 0;
    st_wSecond = 0;
    st_wMilliseconds = 0;

    for (int i = 0; i < 80; i = i + 1) {
        if (i < 10) {
            date[i] = st_wYear % 10 + '0';
            st_wYear = st_wYear / 10;
        }
    }

    for (int i = 0; i < 80; i = i + 1) {
        if (i < 8) {
            time[i] = st_wHour % 10 + '0';
            st_wHour = st_wHour / 10;
        }
    }

    return;
}
