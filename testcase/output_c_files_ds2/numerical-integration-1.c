int int_integration(int from[5], int to[5], int n[5], int func[5])
{
    int h[5];
    h[0] = (to[0] - from[0]) / n[0];
    int sum[5];
    sum[0] = 0;
    int x[5];
    x[0] = from[0];
    for (x[0] = from[0]; x[0] <= (to[0] - h[0]); x[0] = x[0] + h[0])
    {
        sum[0] = sum[0] + func[0];
    }
    int result_leftrect[5];
    result_leftrect[0] = h[0] * sum[0];

    h[0] = (to[0] - from[0]) / n[0];
    sum[0] = 0;
    x[0] = from[0];
    for (x[0] = from[0]; x[0] <= (to[0] - h[0]); x[0] = x[0] + h[0])
    {
        sum[0] = sum[0] + func[0];
    }
    int result_rightrect[5];
    result_rightrect[0] = h[0] * sum[0];

    h[0] = (to[0] - from[0]) / n[0];
    sum[0] = 0;
    x[0] = from[0];
    for (x[0] = from[0]; x[0] <= (to[0] - h[0]); x[0] = x[0] + h[0])
    {
        sum[0] = sum[0] + func[0];
    }
    int result_midrect[5];
    result_midrect[0] = h[0] * sum[0];

    h[0] = (to[0] - from[0]) / n[0];
    sum[0] = func[0] + func[0];
    int i[5];
    for (i[0] = 1; i[0] < n[0]; i[0] = i[0] + 1)
    {
        sum[0] = sum[0] + 2 * func[0];
    }
    int result_trapezium[5];
    result_trapezium[0] = h[0] * sum[0] / 2;

    h[0] = (to[0] - from[0]) / n[0];
    int sum1[5];
    sum1[0] = 0;
    int sum2[5];
    sum2[0] = 0;
    for (i[0] = 0; i[0] < n[0]; i[0] = i[0] + 1)
    {
        sum1[0] = sum1[0] + func[0];
    }
    for (i[0] = 1; i[0] < n[0]; i[0] = i[0] + 1)
    {
        sum2[0] = sum2[0] + func[0];
    }
    int result_simpson[5];
    result_simpson[0] = h[0] / 6 * (func[0] + func[0] + 4 * sum1[0] + 2 * sum2[0]);

    return;
}
