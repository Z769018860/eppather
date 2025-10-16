int kaprekar(int n[5], int base[5])
{
    int nn[5];
    nn[0] = n[0] * n[0];
    int r[5];
    int tens[5];
    tens[0] = 1;

    if ((nn[0] - n[0]) % (base[0] - 1)) 
    {
        return 0;
    }

    for (; tens[0] < n[0]; tens[0] = tens[0] * base[0])
    {
    }
    if (n[0] == tens[0]) 
    {
        return 1 == n[0];
    }

    for (; (r[0] = nn[0] % tens[0]) < n[0]; tens[0] = tens[0] * base[0])
    {
        if (nn[0] / tens[0] + r[0] == n[0]) 
        {
            return tens[0];
        }
    }

    return 0;
}

void print_num(int n[5], int base[5])
{
    int q[5];
    int div[5];
    div[0] = base[0];

    for (; div[0] < n[0]; div[0] = div[0] * base[0])
    {
    }
    for (; n[0] && (div[0] = div[0] / base[0]); )
    {
        q[0] = n[0] / div[0];
        n[0] = n[0] - q[0] * div[0];
    }
    return;
}

void merged_function(int n[5], int base[5])
{
    int nn[5];
    nn[0] = n[0] * n[0];
    int r[5];
    int tens[5];
    tens[0] = 1;

    if ((nn[0] - n[0]) % (base[0] - 1)) 
    {
        return;
    }

    for (; tens[0] < n[0]; tens[0] = tens[0] * base[0])
    {
    }
    if (n[0] == tens[0]) 
    {
        return;
    }

    for (; (r[0] = nn[0] % tens[0]) < n[0]; tens[0] = tens[0] * base[0])
    {
        if (nn[0] / tens[0] + r[0] == n[0]) 
        {
            return;
        }
    }

    int q[5];
    int div[5];
    div[0] = base[0];

    for (; div[0] < n[0]; div[0] = div[0] * base[0])
    {
    }
    for (; n[0] && (div[0] = div[0] / base[0]); )
    {
        q[0] = n[0] / div[0];
        n[0] = n[0] - q[0] * div[0];
    }
    return;
}
