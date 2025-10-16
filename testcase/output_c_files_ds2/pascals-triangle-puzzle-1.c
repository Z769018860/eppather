void pascal(int a, int b, int mid, int top, int* x, int* y, int* z)
{
    int temp[5];
    temp[0] = top - 4 * (a + b);
    temp[1] = temp[0] / 7;
    temp[2] = temp[0] % 7;
    if (temp[2] != 0)
    {
        x[0] = 0;
        return;
    }
    y[0] = temp[1];
    x[0] = mid - 2 * a - y[0];
    z[0] = y[0] - x[0];
    return;
}
