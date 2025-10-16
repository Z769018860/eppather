double rk4(double(*f)(double, double), double dx, double x, double y)
{
    double k1;
    double k2;
    double k3;
    double k4;
    k1 = dx * f(x, y);
    k2 = dx * f(x + dx / 2, y + k1 / 2);
    k3 = dx * f(x + dx / 2, y + k2 / 2);
    k4 = dx * f(x + dx, y + k3);
    return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

double rate(double x, double y)
{
    return x * sqrt(y);
}

void combined_function()
{
    double y[101];
    double x;
    double y2;
    double x0 = 0;
    double x1 = 10;
    double dx = 0.1;
    int n = 101;
    int i;
    y[0] = 1;
    for (i = 1; i < n; i = i + 1)
    {
        y[i] = rk4(rate, dx, x0 + dx * (i - 1), y[i - 1]);
    }
    for (i = 0; i < n; i = i + 10)
    {
        x = x0 + dx * i;
        y2 = pow(x * x / 4 + 1, 2);
    }
    return;
}
