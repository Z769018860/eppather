double rho(double *x, double *y, double *r, int i, int n)
{
    double ret_val;
    int idx;
    if (n < 0)
    {
        ret_val = 0;
    }
    else
    {
        if (n == 0)
        {
            ret_val = y[i];
        }
        else
        {
            idx = (32 - 1 - n) * (32 - n) / 2 + i;
            if (r[idx] != r[idx])
            {
                r[idx] = (x[i] - x[i + n]) / (rho(x, y, r, i, n - 1) - rho(x, y, r, i + 1, n - 1)) + rho(x, y, r, i + 1, n - 2);
            }
            ret_val = r[idx];
        }
    }
    return ret_val;
}

double thiele(double *x, double *y, double *r, double xin, int n)
{
    double ret_val;
    if (n > 32 - 1)
    {
        ret_val = 1;
    }
    else
    {
        ret_val = rho(x, y, r, 0, n) - rho(x, y, r, 0, n - 2) + (xin - x[n]) / thiele(x, y, r, xin, n + 1);
    }
    return ret_val;
}

return;
