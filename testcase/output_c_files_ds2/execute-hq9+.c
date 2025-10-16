void runCode(const char *code)
{
    int c_len[5];
    c_len[0] = 0;
    int i[5];
    i[0] = 0;
    int bottles[5];
    unsigned accumulator[5];
    accumulator[0] = 0;
    
    while (code[c_len[0]] != 0)
    {
        c_len[0] = c_len[0] + 1;
    }
    
    for (i[0] = 0; i[0] < c_len[0]; i[0] = i[0] + 1)
    {
        if (code[i[0]] == 'Q')
        {
        }
        else if (code[i[0]] == 'H')
        {
        }
        else if (code[i[0]] == '9')
        {
            bottles[0] = 99;
            for (i[1] = 0; i[1] < 5; i[1] = i[1] + 1)
            {
                if (bottles[0] > 0)
                {
                    bottles[0] = bottles[0] - 1;
                }
            }
        }
        else if (code[i[0]] == '+')
        {
            accumulator[0] = accumulator[0] + 1;
        }
    }
    return;
}
