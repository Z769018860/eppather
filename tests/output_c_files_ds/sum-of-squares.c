int squaredsum(int* l, int e)
{
    int sum = 0;
    int i;
    for(i = 0; i < e; i = i + 1)
    {
        sum = sum + l[i] * l[i];
    }
    return sum;
}
