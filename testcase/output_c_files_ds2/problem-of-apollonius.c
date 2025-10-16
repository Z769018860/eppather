int apollonius_in(int aa_c_re[3], int aa_c_im[3], int aa_r[3], int ss[3], int flip, int divert, int verbose)
{
    int n_re[3];
    int n_im[3];
    int x_re[3];
    int x_im[3];
    int t_re[3];
    int t_im[3];
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
    int a_re;
    int a_im;
    int b_re;
    int b_im;
    int temp_re;
    int temp_im;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    int i;
    
    iter = 0;
    res = 0;
    diff = 1;
    diff_old = -1;
    
    for (i = 0; i < 3; i = i + 1) {
        s[i] = ss[i] ? 1 : -1;
        x_re[i] = aa_c_re[i];
        x_im[i] = aa_c_im[i];
    }
    
    while (diff > 0) {
        a_re = x_re[0] - x_re[2];
        a_im = x_im[0] - x_im[2];
        b_re = x_re[1] - x_re[2];
        b_im = x_im[1] - x_im[2];
        diff = 0;
        axb = -(a_re * b_im - a_im * b_re);
        temp1 = a_re * a_re + a_im * a_im;
        temp2 = b_re * b_re + b_im * b_im;
        temp3 = (a_re - b_re) * (a_re - b_re) + (a_im - b_im) * (a_im - b_im);
        d = temp1 * temp2 * temp3;
        
        r = d / (2 * axb);
        if (r < 0) {
            r = -r;
        }
        temp1 = temp1 * b_re - temp2 * a_re;
        temp2 = temp1 * b_im - temp2 * a_im;
        center_re = (-temp2) / (2 * axb) + x_re[2];
        center_im = (temp1) / (2 * axb) + x_im[2];
        
        if (!axb && flip != -1 && !divert) {
            if (!d) {
                return 0;
            }
            divert = 1;
            res = apollonius_in(aa_c_re, aa_c_im, aa_r, ss, -1, 1, verbose);
        }
        
        for (i = 0; i < 3; i = i + 1) {
            if (axb) {
                n_re[i] = aa_c_re[i] - center_re;
                n_im[i] = aa_c_im[i] - center_im;
            } else {
                n_re[i] = -a_im * flip;
                n_im[i] = a_re * flip;
            }
            temp1 = n_re[i] * n_re[i] + n_im[i] * n_im[i];
            temp2 = aa_r[i] * s[i];
            t_re[i] = aa_c_re[i] + (n_re[i] * temp2) / temp1;
            t_im[i] = aa_c_im[i] + (n_im[i] * temp2) / temp1;
        }
        
        for (i = 0; i < 3; i = i + 1) {
            temp1 = t_re[i] - x_re[i];
            temp2 = t_im[i] - x_im[i];
            diff = diff + temp1 * temp1 + temp2 * temp2;
            x_re[i] = t_re[i];
            x_im[i] = t_im[i];
        }
        
        if (diff >= diff_old && diff_old >= 0) {
            if (iter > 20) {
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
    int sum;
    int j;
    
    sum = 0;
    for (i = 0; i < 8; i = i + 1) {
        s[0] = i & 1;
        s[1] = i & 2;
        s[2] = i & 4;
        
        if (s[0] && !aa_r[0]) {
            continue;
        }
        if (s[1] && !aa_r[1]) {
            continue;
        }
        if (s[2] && !aa_r[2]) {
            continue;
        }
        sum = sum + apollonius_in(aa_c_re, aa_c_im, aa_r, s, 1, 0, 0);
    }
    return sum;
}
