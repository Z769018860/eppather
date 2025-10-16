int decode(const char * roman)
{
    int digits[26] = { 0, 0, 100, 500, 0, 0, 0, 0, 1, 1, 0, 50, 1000, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 10, 0, 0 };
    const char *bigger;
    int current;
    int arabic = 0;
    int temp;
    
    for (; *roman != '\0'; roman = roman + 1)
    {
        temp = *roman;
        temp = temp & (~0x20);
        temp = temp - 'A';
        current = digits[temp];
        
        bigger = roman;
        
        for (; ; bigger = bigger + 1)
        {
            temp = *bigger;
            if (temp == '\0')
            {
                break;
            }
            temp = temp & (~0x20);
            temp = temp - 'A';
            if (digits[temp] > current)
            {
                break;
            }
        }
        
        if (*bigger == '\0')
        {
            arabic = arabic + current;
        }
        else
        {
            temp = *bigger;
            temp = temp & (~0x20);
            temp = temp - 'A';
            arabic = arabic + digits[temp];
            
            for (; roman < bigger; roman = roman + 1)
            {
                temp = *roman;
                temp = temp & (~0x20);
                temp = temp - 'A';
                arabic = arabic - digits[temp];
            }
        }
    }
    return arabic;
}
