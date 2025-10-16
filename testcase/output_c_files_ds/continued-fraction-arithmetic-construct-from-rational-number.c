int r2cf(int* numerator, int* denominator)
{
    int quotient;
    int temp;
    quotient = 0;
    if (*denominator != 0)
    {
        quotient = *numerator / *denominator;
        temp = *numerator;
        *numerator = *denominator;
        *denominator = temp % *denominator;
    }
    return quotient;
}
