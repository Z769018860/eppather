int is_prime(unsigned int n)
{
    if (n <= 3)
    {
        if (n > 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if ((n % 2 == 0) || (n % 3 == 0))
        {
            return 0;
        }
        else
        {
            unsigned int i;
            for (i = 5; i * i <= n; i = i + 6)
            {
                if ((n % i == 0) || (n % (i + 2) == 0))
                {
                    return 0;
                }
            }
            return 1;
        }
    }
}

void carmichael3(int p1)
{
    int h3[5];
    int d[5];
    int p2[5];
    int p3[5];
    int temp1[5];
    int temp2[5];
    int temp3[5];
    int temp4[5];
    
    if (is_prime(p1) == 0)
    {
        return;
    }
    
    for (h3[0] = 1; h3[0] < p1; h3[0] = h3[0] + 1)
    {
        for (d[0] = 1; d[0] < h3[0] + p1; d[0] = d[0] + 1)
        {
            temp1[0] = h3[0] + p1;
            temp2[0] = p1 - 1;
            temp3[0] = temp1[0] * temp2[0];
            if ((temp3[0] % d[0] == 0) && ((((-p1 * p1) % h3[0]) + h3[0]) % h3[0] == d[0] % h3[0]))
            {
                temp4[0] = (p1 - 1) * (h3[0] + p1);
                p2[0] = 1 + (temp4[0] / d[0]);
                if (is_prime(p2[0]) == 0)
                {
                    continue;
                }
                p3[0] = 1 + (p1 * p2[0] / h3[0]);
                if ((is_prime(p3[0]) == 0) || ((p2[0] * p3[0]) % (p1 - 1) != 1))
                {
                    continue;
                }
            }
        }
    }
    return;
}
