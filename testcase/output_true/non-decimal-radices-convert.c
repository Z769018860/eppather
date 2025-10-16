int to_base(int num, int base, int out_len, char out[66], char tbl[37])
{
    int buf[66];
    int n;
    int i;
    int len = 0;
    int neg = 0;
    if (base > 36)
    {
        return 0;
    }
    n = num;
    if (num < 0)
    {
        neg = 1;
        n = (~num) + 1;
    }
    for (i = 0; i < 66; i = i + 1)
    {
        buf[i] = 0;
    }
    do
    {
        buf[len] = tbl[n % base];
        len = len + 1;
        n = n / base;
    } while (n != 0);
    for (i = neg; len > 0; i = i + 1)
    {
        len = len - 1;
        out[i] = buf[len];
    }
    if (neg != 0)
    {
        out[0] = 45;
    }
    return;
}

int from_base(char num_str[5], int base)
{
    int result = 0;
    int i;
    int digit;
    for (i = 0; i < 5; i = i + 1)
    {
        if (num_str[i] == 0)
        {
            break;
        }
        if (num_str[i] >= 48 && num_str[i] <= 57)
        {
            digit = num_str[i] - 48;
        }
        else if (num_str[i] >= 97 && num_str[i] <= 122)
        {
            digit = num_str[i] - 87;
        }
        else if (num_str[i] >= 65 && num_str[i] <= 90)
        {
            digit = num_str[i] - 55;
        }
        else
        {
            break;
        }
        if (digit >= base)
        {
            break;
        }
        result = result * base + digit;
    }
    return result;
}
