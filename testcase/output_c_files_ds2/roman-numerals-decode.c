int decode(const char * roman, int digits_len, int digits_val0, int digits_val1, int digits_val2, int digits_val3, int digits_val4, int digits_val5, int digits_val6, int digits_val7, int digits_val8, int digits_val9, int digits_val10, int digits_val11, int digits_val12, int digits_val13, int digits_val14, int digits_val15, int digits_val16, int digits_val17, int digits_val18, int digits_val19, int digits_val20, int digits_val21, int digits_val22, int digits_val23, int digits_val24, int digits_val25)
{
    int digits[26];
    digits[0] = digits_val0;
    digits[1] = digits_val1;
    digits[2] = digits_val2;
    digits[3] = digits_val3;
    digits[4] = digits_val4;
    digits[5] = digits_val5;
    digits[6] = digits_val6;
    digits[7] = digits_val7;
    digits[8] = digits_val8;
    digits[9] = digits_val9;
    digits[10] = digits_val10;
    digits[11] = digits_val11;
    digits[12] = digits_val12;
    digits[13] = digits_val13;
    digits[14] = digits_val14;
    digits[15] = digits_val15;
    digits[16] = digits_val16;
    digits[17] = digits_val17;
    digits[18] = digits_val18;
    digits[19] = digits_val19;
    digits[20] = digits_val20;
    digits[21] = digits_val21;
    digits[22] = digits_val22;
    digits[23] = digits_val23;
    digits[24] = digits_val24;
    digits[25] = digits_val25;
    
    const char *bigger;
    int current;
    int arabic[5];
    arabic[0] = 0;
    
    for (; *roman != 0; roman = roman + 1)
    {
        current = digits[(~(32) & (*roman)) - 65];
        bigger = roman;
        
        for (; digits[(~(32) & (*bigger)) - 65] <= current && *bigger != 0; bigger = bigger + 1)
        {
        }
        
        if (*bigger == 0)
        {
            arabic[0] = arabic[0] + current;
        }
        else
        {
            arabic[0] = arabic[0] + digits[(~(32) & (*bigger)) - 65];
            for (; roman < bigger; roman = roman + 1)
            {
                arabic[0] = arabic[0] - digits[(~(32) & (*roman)) - 65];
            }
        }
    }
    return arabic[0];
}
