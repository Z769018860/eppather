void serialize_value(int gen[5], int val[5], int parse_numbers)
{
    int i;
    int type[5];
    type[0] = val[0];
    
    if (type[0] == 0)
    {
        int string_len[5];
        string_len[0] = 0;
        for (i = 0; i < 5; i = i + 1)
        {
            if (val[1] != 0)
            {
                string_len[0] = string_len[0] + 1;
            }
        }
    }
    else if (type[0] == 1)
    {
        if (parse_numbers != 0 && (val[1] & 1) != 0)
        {
        }
        else if (parse_numbers != 0 && (val[1] & 2) != 0)
        {
        }
        else
        {
            int number_len[5];
            number_len[0] = 0;
            for (i = 0; i < 5; i = i + 1)
            {
                if (val[1] != 0)
                {
                    number_len[0] = number_len[0] + 1;
                }
            }
        }
    }
    else if (type[0] == 2)
    {
        for (i = 0; i < 5; i = i + 1)
        {
            int key_len[5];
            key_len[0] = 0;
            for (int j = 0; j < 5; j = j + 1)
            {
                if (val[1] != 0)
                {
                    key_len[0] = key_len[0] + 1;
                }
            }
            serialize_value(gen, val, parse_numbers);
        }
    }
    else if (type[0] == 3)
    {
        for (i = 0; i < 5; i = i + 1)
        {
            serialize_value(gen, val, parse_numbers);
        }
    }
    else if (type[0] == 4)
    {
    }
    else if (type[0] == 5)
    {
    }
    else if (type[0] == 6)
    {
    }
    else
    {
    }
    return;
}
