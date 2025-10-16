int decode(const char *s, char *dec)
{
    char *o;
    const char *end;
    int c;
    int len;
    int i;
    int temp;
    int digit1;
    int digit2;
    
    len = 0;
    while (s[len] != '\0')
    {
        len = len + 1;
    }
    end = s + len;
    o = dec;
    
    for (; s <= end; o = o + 1)
    {
        c = *s;
        s = s + 1;
        if (c == '+')
        {
            c = ' ';
        }
        else if (c == '%')
        {
            digit1 = *s;
            s = s + 1;
            digit2 = *s;
            s = s + 1;
            if (!((digit1 >= '0' && digit1 <= '9') || (digit1 >= 'a' && digit1 <= 'f') || (digit1 >= 'A' && digit1 <= 'F')))
            {
                return -1;
            }
            if (!((digit2 >= '0' && digit2 <= '9') || (digit2 >= 'a' && digit2 <= 'f') || (digit2 >= 'A' && digit2 <= 'F')))
            {
                return -1;
            }
            temp = 0;
            if (digit1 >= '0' && digit1 <= '9')
            {
                temp = digit1 - '0';
            }
            else if (digit1 >= 'a' && digit1 <= 'f')
            {
                temp = digit1 - 'a' + 10;
            }
            else if (digit1 >= 'A' && digit1 <= 'F')
            {
                temp = digit1 - 'A' + 10;
            }
            temp = temp * 16;
            if (digit2 >= '0' && digit2 <= '9')
            {
                temp = temp + (digit2 - '0');
            }
            else if (digit2 >= 'a' && digit2 <= 'f')
            {
                temp = temp + (digit2 - 'a' + 10);
            }
            else if (digit2 >= 'A' && digit2 <= 'F')
            {
                temp = temp + (digit2 - 'A' + 10);
            }
            c = temp;
        }
        if (dec)
        {
            *o = c;
        }
    }
    return o - dec;
}
