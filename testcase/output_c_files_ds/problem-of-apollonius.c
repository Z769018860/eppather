int apollonius_in(int aa_c_re[3], int aa_c_im[3], int aa_r[3], int ss[3], int flip, int divert)
{
    int x_re[3];
    int x_im[3];
    int s[3];
    int iter;
    int res;
    int diff;
    int diff_old;
    int axb;
    int d;
    int r;
    int center_re;
    int center_im;
    int n_re[3];
    int n_im[3];
    int t_re[3];
    int t_im[3];
    int a_re;
    int a_im;
    int b_re;
    int b_im;
    int temp_re;
    int temp_im;
    int abs2_a;
    int abs2_b;
    int abs2_a_minus_b;
    int i;
    
    iter = 0;
    res = 0;
    diff = 1;
    diff_old = -1;
    
    for (i = 0; i < 3; i = i + 1)
    {
        s[i] = ss[i] ? 1 : -1;
        x_re[i] = aa_c_re[i];
        x_im[i] = aa_c_im[i];
    }
    
    while (diff > 0)
    {
        a_re = x_re[0] - x_re[2];
        a_im = x_im[0] - x_im[2];
        b_re = x_re[1] - x_re[2];
        b_im = x_im[1] - x_im[2];
        diff = 0;
        axb = -(a_re * b_im - a_im * b_re);
        abs2_a = a_re * a_re + a_im * a_im;
        abs2_b = b_re * b_re + b_im * b_im;
        abs2_a_minus_b = (a_re - b_re) * (a_re - b_re) + (a_im - b_im) * (a_im - b_im);
        d = abs2_a * abs2_b * abs2_a_minus_b;
        
        r = d / (2 * axb);
        if (r < 0)
        {
            r = -r;
        }
        temp_re = (abs2_a * b_re - abs2_b * a_re);
        temp_im = (abs2_a * b_im - abs2_b * a_im);
        center_re = (-temp_im) / (2 * axb) + x_re[2];
        center_im = (temp_re) / (2 * axb) + x_im[2];
        
        if (axb == 0 && flip != -1 && divert == 0)
        {
            if (d == 0)
            {
                return 0;
            }
            divert = 1;
            res = apollonius_in(aa_c_re, aa_c_im, aa_r, ss, -1, 1);
        }
        
        for (i = 0; i < 3; i = i + 1)
        {
            if (axb != 0)
            {
                n_re[i] = aa_c_re[i] - center_re;
                n_im[i] = aa_c_im[i] - center_im;
            }
            else
            {
                n_re[i] = -a_im * flip;
                n_im[i] = a_re * flip;
            }
            temp_re = n_re[i] * n_re[i] + n_im[i] * n_im[i];
            temp_im = aa_r[i] * s[i];
            t_re[i] = aa_c_re[i] + (n_re[i] * temp_im) / temp_re;
            t_im[i] = aa_c_im[i] + (n_im[i] * temp_im) / temp_re;
        }
        
        for (i = 0; i < 3; i = i + 1)
        {
            diff = diff + (t_re[i] - x_re[i]) * (t_re[i] - x_re[i]) + (t_im[i] - x_im[i]) * (t_im[i] - x_im[i]);
            x_re[i] = t_re[i];
            x_im[i] = t_im[i];
        }
        
        if (diff >= diff_old && diff_old >= 0)
        {
            if (iter > 20)
            {
                return res;
            }
            iter = iter + 1;
        }
        diff_old = diff;
    }
    return res + 1;
}

int apollonius(int aa_c_re[3], int aa_c_im[3], int aa_r[3])
{
    int s[3];
    int i;
    int j;
    int sum;
    
    sum = 0;
    for (i = 0; i < 8; i = i + 1)
    {
        s[0] = i & 1;
        s[1] = i & 2;
        s[2] = i & 4;
        
        if (s[0] != 0 && aa_r[0] == 0)
        {
            continue;
        }
        if (s[1] != 0 && aa_r[1] == 0)
        {
            continue;
        }
        if (s[2] != 0 && aa_r[2] == 0)
        {
            continue;
        }
        sum = sum + apollonius_in(aa_c_re, aa_c_im, aa_r, s, 1, 0);
    }
    return sum;
}
