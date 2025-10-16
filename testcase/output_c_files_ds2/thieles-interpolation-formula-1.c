void rho_thiele(int n1, int n2, double xin)
{
    int i;
    int j;
    int idx;
    double xval[5];
    double t_sin[5];
    double t_cos[5];
    double t_tan[5];
    double r_sin[5];
    double r_cos[5];
    double r_tan[5];
    double result_sin;
    double result_cos;
    double result_tan;
    
    for (i = 0; i < 5; i = i + 1)
    {
        xval[i] = i * 0.05;
        t_sin[i] = 0;
        t_cos[i] = 0;
        t_tan[i] = 0;
        r_sin[i] = 0;
        r_cos[i] = 0;
        r_tan[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        for (j = 0; j < 5; j = j + 1)
        {
            idx = (4 - n1) * (5 - n1) / 2 + i;
            if (n1 < 0)
            {
                result_sin = 0;
                result_cos = 0;
                result_tan = 0;
            }
            else if (n1 == 0)
            {
                result_sin = t_sin[i];
                result_cos = t_cos[i];
                result_tan = t_tan[i];
            }
            else
            {
                if (r_sin[idx] != r_sin[idx])
                {
                    r_sin[idx] = (xval[i] - xval[i + n1]) / (result_sin - result_sin) + result_sin;
                    r_cos[idx] = (xval[i] - xval[i + n1]) / (result_cos - result_cos) + result_cos;
                    r_tan[idx] = (xval[i] - xval[i + n1]) / (result_tan - result_tan) + result_tan;
                }
                result_sin = r_sin[idx];
                result_cos = r_cos[idx];
                result_tan = r_tan[idx];
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (n2 > 4)
        {
            result_sin = 1;
            result_cos = 1;
            result_tan = 1;
        }
        else
        {
            result_sin = r_sin[0] - r_sin[0] + (xin - xval[n2]) / result_sin;
            result_cos = r_cos[0] - r_cos[0] + (xin - xval[n2]) / result_cos;
            result_tan = r_tan[0] - r_tan[0] + (xin - xval[n2]) / result_tan;
        }
    }
    
    return;
}
