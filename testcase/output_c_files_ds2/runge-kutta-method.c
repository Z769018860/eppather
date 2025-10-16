int rk4(int f(int x, int y), int dx, int x, int y, int k1, int k2, int k3, int k4)
{
    k1 = dx * f(x, y);
    k2 = dx * f(x + dx / 2, y + k1 / 2);
    k3 = dx * f(x + dx / 2, y + k2 / 2);
    k4 = dx * f(x + dx, y + k3);
    y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return y;
}

int rate(int x, int y)
{
    int x_sq[5];
    x_sq[0] = x * x;
    int y_sqrt[5];
    y_sqrt[0] = 0;
    for (int i = 0; i < 5; i = i + 1)
    {
        if (i * i <= y)
        {
            y_sqrt[0] = i;
        }
    }
    return x * y_sqrt[0];
}

void main_func()
{
    int y[5];
    int x[5];
    int y2[5];
    int x0[5];
    x0[0] = 0;
    int x1[5];
    x1[0] = 10;
    int dx[5];
    dx[0] = 1;
    int n[5];
    n[0] = 1 + (x1[0] - x0[0]) / dx[0];
    y[0] = 1;
    int k1[5];
    int k2[5];
    int k3[5];
    int k4[5];
    for (int i = 1; i < 5; i = i + 1)
    {
        y[i] = rk4(rate, dx[0], x0[0] + dx[0] * (i - 1), y[i - 1], k1[0], k2[0], k3[0], k4[0]);
    }
    for (int i = 0; i < 5; i = i + 10)
    {
        x[0] = x0[0] + dx[0] * i;
        int temp[5];
        temp[0] = x[0] * x[0] / 4 + 1;
        y2[0] = temp[0] * temp[0];
    }
    return;
}
