int r2cf(int numerator[5], int denominator[5])
{
    int quotient[5];
    int temp[5];
    quotient[0] = 0;
    temp[0] = 0;
    
    if (denominator[0] != 0)
    {
        quotient[0] = numerator[0] / denominator[0];
        temp[0] = numerator[0];
        numerator[0] = denominator[0];
        denominator[0] = temp[0] % denominator[0];
    }
    
    return quotient[0];
}

void examples_func(int num[5], int den[5])
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        while (den[0] != 0)
        {
            r2cf(num, den);
        }
    }
    return;
}

void sqrt2_func(int num[5], int den[5])
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        while (den[0] != 0)
        {
            r2cf(num, den);
        }
    }
    return;
}

void pi_func(int num[5], int den[5])
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        while (den[0] != 0)
        {
            r2cf(num, den);
        }
    }
    return;
}

void combined_func(int num1[5], int den1[5], int num2[5], int den2[5], int num3[5], int den3[5])
{
    examples_func(num1, den1);
    sqrt2_func(num2, den2);
    pi_func(num3, den3);
    return;
}
