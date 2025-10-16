int ToRoman(int num, int buf[5], int buflen, int romanDgts[15])
{
    int roman[5];
    int rdix;
    int r;
    int v;
    int i;
    int j;
    int k;
    
    for (i = 0; i < 15; i = i + 1)
    {
        romanDgts[i] = 0;
    }
    romanDgts[0] = 105;
    romanDgts[1] = 118;
    romanDgts[2] = 120;
    romanDgts[3] = 108;
    romanDgts[4] = 99;
    romanDgts[5] = 100;
    romanDgts[6] = 109;
    romanDgts[7] = 86;
    romanDgts[8] = 88;
    romanDgts[9] = 76;
    romanDgts[10] = 67;
    romanDgts[11] = 68;
    romanDgts[12] = 77;
    romanDgts[13] = 95;
    
    for (i = 0; i < 5; i = i + 1)
    {
        roman[i] = 0;
    }
    roman[0] = buf[0] + buflen;
    roman[0] = roman[0] - 1;
    roman[0] = 0;
    
    if (num >= 4000000)
    {
        return 0;
    }
    
    for (rdix = 0; rdix < 14; rdix = rdix + 2)
    {
        if (num == 0)
        {
            break;
        }
        v = (num % 10) / 5;
        r = num % 5;
        num = num / 10;
        if (r == 4)
        {
            if (roman[0] < buf[0] + 2)
            {
                return 0;
            }
            roman[0] = roman[0] - 1;
            roman[0] = romanDgts[rdix + 1 + v];
            roman[0] = roman[0] - 1;
            roman[0] = romanDgts[rdix];
        }
        else
        {
            if (roman[0] < buf[0] + r + v)
            {
                return 0;
            }
            j = r;
            for (k = 0; k < j; k = k + 1)
            {
                roman[0] = roman[0] - 1;
                roman[0] = romanDgts[rdix];
            }
            if (v == 1)
            {
                roman[0] = roman[0] - 1;
                roman[0] = romanDgts[rdix + 1];
            }
        }
    }
    return roman[0];
}
