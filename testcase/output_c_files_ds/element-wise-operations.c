void eop_add(double** a, double** b, double** c, int w, int h)
{
    int i;
    int j;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return;
}

void eop_sub(double** a, double** b, double** c, int w, int h)
{
    int i;
    int j;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return;
}

void eop_mul(double** a, double** b, double** c, int w, int h)
{
    int i;
    int j;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
    return;
}

void eop_div(double** a, double** b, double** c, int w, int h)
{
    int i;
    int j;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            c[i][j] = a[i][j] / b[i][j];
        }
    }
    return;
}

void eop_s_mul(double** a, double s, double** b, int w, int h)
{
    int i;
    int j;
    double x;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            x = a[i][j];
            b[i][j] = x * s;
        }
    }
    return;
}

void eop_s_div(double** a, double s, double** b, int w, int h)
{
    int i;
    int j;
    double x;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            x = a[i][j];
            b[i][j] = x / s;
        }
    }
    return;
}

void eop_s_add(double** a, double s, double** b, int w, int h)
{
    int i;
    int j;
    double x;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            x = a[i][j];
            b[i][j] = x + s;
        }
    }
    return;
}

void eop_s_sub(double** a, double s, double** b, int w, int h)
{
    int i;
    int j;
    double x;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            x = a[i][j];
            b[i][j] = x - s;
        }
    }
    return;
}

void eop_s_pow(double** a, double s, double** b, int w, int h)
{
    int i;
    int j;
    double x;
    double result;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            x = a[i][j];
            result = 1.0;
            for (int k = 0; k < (int)s; k = k + 1)
            {
                result = result * x;
            }
            b[i][j] = result;
        }
    }
    return;
}
