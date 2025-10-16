void pascal(int a, int b, int mid, int top, int* x, int* y, int* z)
{
    int temp1;
    int temp2;
    int temp3;
    temp1 = top - 4 * (a + b);
    temp2 = temp1 / 7;
    temp3 = temp1 % 7;
    if (temp3 != 0)
    {
        *x = 0;
        return;
    }
    *y = temp2;
    *x = mid - 2 * a - *y;
    *z = *y - *x;
    return;
}
