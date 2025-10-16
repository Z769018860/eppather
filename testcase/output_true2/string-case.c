void str_case_convert(int s[5], int is_upper)
{
    int i;
    for(i = 0; i < 5; i = i + 1)
    {
        if(s[i] == 0)
        {
            break;
        }
        if(is_upper != 0)
        {
            if(s[i] >= 97 && s[i] <= 122)
            {
                s[i] = s[i] - 32;
            }
        }
        else
        {
            if(s[i] >= 65 && s[i] <= 90)
            {
                s[i] = s[i] + 32;
            }
        }
    }
    return;
}
