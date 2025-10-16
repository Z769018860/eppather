char to_base(int num, int base, char out[66])
{
    char tbl[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char buf[66] = {'\0'};
    int n;
    int i;
    int len = 0;
    int neg = 0;
    if (base > 36)
    {
        return 0;
    }
    if (num < 0)
    {
        neg = 1;
        n = (~num) + 1;
    }
    else
    {
        n = num;
    }
    for (len = 0; n > 0; len = len + 1)
    {
        buf[len] = tbl[n % base];
        n = n / base;
    }
    for (i = neg; len > 0; i = i + 1)
    {
        len = len - 1;
        out[i] = buf[len];
    }
    if (neg)
    {
        out[0] = '-';
    }
    return;
}
