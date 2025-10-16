int cmp_rec(const void *aa, const void *bb)
{
    const char *a_s = *((const char**)aa);
    const char *b_s = *((const char**)bb);
    if (a_s == b_s)
    {
        return 0;
    }
    if (a_s == 0)
    {
        return 1;
    }
    if (b_s == 0)
    {
        return -1;
    }
    for (int i = 0; i < 10; i = i + 1)
    {
        if (a_s[i] != b_s[i])
        {
            return a_s[i] - b_s[i];
        }
    }
    return 0;
}

void read_file()
{
    int txt[10000];
    int rec_s[1000];
    int rec_ln[1000];
    int rec_bad[1000];
    int lines = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int di = 0;
    int bad = 0;
    int ptr = 0;
    int end = 0;
    int val = 0;
    int is_bad = 0;

    for (i = 0; i < 10000; i = i + 1)
    {
        txt[i] = 0;
    }
    for (i = 0; i < 1000; i = i + 1)
    {
        rec_s[i] = 0;
        rec_ln[i] = 0;
        rec_bad[i] = 0;
    }

    for (i = 0; i < 10000; i = i + 1)
    {
        if (txt[i] == '\n')
        {
            txt[i] = '\0';
            lines = lines + 1;
        }
    }

    rec_s[0] = 0;
    rec_ln[0] = 1;
    for (i = 0; i < lines; i = i + 1)
    {
        if (i + 1 < lines)
        {
            j = 0;
            while (txt[rec_s[i] + j] != '\0')
            {
                j = j + 1;
            }
            rec_s[i + 1] = rec_s[i] + j + 1;
            rec_ln[i + 1] = i + 2;
        }

        is_bad = 0;
        ptr = rec_s[i];
        for (j = 0; j < 4; j = j + 1)
        {
            if (txt[ptr + j] < '0' || txt[ptr + j] > '9')
            {
                is_bad = 1;
            }
        }
        if (txt[ptr + 4] != '-')
        {
            is_bad = 1;
        }
        ptr = ptr + 5;
        for (j = 0; j < 2; j = j + 1)
        {
            if (txt[ptr + j] < '0' || txt[ptr + j] > '9')
            {
                is_bad = 1;
            }
        }
        if (txt[ptr + 2] != '-')
        {
            is_bad = 1;
        }
        ptr = ptr + 3;
        for (j = 0; j < 2; j = j + 1)
        {
            if (txt[ptr + j] < '0' || txt[ptr + j] > '9')
            {
                is_bad = 1;
            }
        }
        if (is_bad)
        {
            rec_s[i] = 0;
            continue;
        }
        ptr = rec_s[i] + 10;

        k = 0;
        for (j = 0; j < 25; j = j + 1)
        {
            val = 0;
            while (txt[ptr] == ' ')
            {
                ptr = ptr + 1;
            }
            if (txt[ptr] < '0' || txt[ptr] > '9')
            {
                break;
            }
            while (txt[ptr] >= '0' && txt[ptr] <= '9')
            {
                val = val * 10 + (txt[ptr] - '0');
                ptr = ptr + 1;
            }
            k = k + 1;
            while (txt[ptr] == ' ')
            {
                ptr = ptr + 1;
            }
            di = 0;
            if (txt[ptr] < '0' || txt[ptr] > '9')
            {
                break;
            }
            while (txt[ptr] >= '0' && txt[ptr] <= '9')
            {
                di = di * 10 + (txt[ptr] - '0');
                ptr = ptr + 1;
            }
            k = k + 1;
            if (di < 1)
            {
                rec_bad[i] = 1;
            }
        }

        if (k != 48)
        {
            rec_s[i] = 0;
        }
    }

    for (i = 0; i < lines; i = i + 1)
    {
        for (j = i + 1; j < lines; j = j + 1)
        {
            if (cmp_rec(&rec_s[i], &rec_s[j]) > 0)
            {
                di = rec_s[i];
                rec_s[i] = rec_s[j];
                rec_s[j] = di;
                di = rec_ln[i];
                rec_ln[i] = rec_ln[j];
                rec_ln[j] = di;
                di = rec_bad[i];
                rec_bad[i] = rec_bad[j];
                rec_bad[j] = di;
            }
        }
    }

    bad = rec_bad[0];
    j = 0;
    for (i = 1; i < lines && rec_s[i] != 0; i = i + 1)
    {
        if (rec_bad[i])
        {
            bad = bad + 1;
        }
        is_bad = 0;
        for (k = 0; k < 10; k = k + 1)
        {
            if (txt[rec_s[i] + k] != txt[rec_s[j] + k])
            {
                is_bad = 1;
                break;
            }
        }
        if (is_bad)
        {
            j = i;
        }
    }
    return;
}
