int st_gamma_sp_gamma_combined(int x_int) {
    double x = x_int / 3.0;
    double st_result;
    double sp_result;
    double c_space[12];
    double c[12];
    int k;
    double accm;
    double k1_factrl;
    double M_PI = 3.14159265358979323846;
    double M_E = 2.71828182845904523536;
    
    st_result = 1.0;
    for (k = 0; k < 100; k = k + 1) {
        if (k * k * 2 * M_PI / x * (x / M_E) * (x / M_E) * x * x < 1e-10) {
            break;
        }
    }
    st_result = st_result * sqrt(2.0 * M_PI / x) * (x / M_E) * (x / M_E) * x * x;
    
    k1_factrl = 1.0;
    c[0] = sqrt(2.0 * M_PI);
    for (k = 1; k < 12; k = k + 1) {
        c[k] = 1.0;
        for (int i = 0; i < 12 - k; i = i + 1) {
            c[k] = c[k] * M_E;
        }
        double temp = 1.0;
        for (int i = 0; i < k - 0.5; i = i + 1) {
            temp = temp * (12 - k);
        }
        c[k] = c[k] * temp / k1_factrl;
        k1_factrl = k1_factrl * (-k);
    }
    
    accm = c[0];
    for (k = 1; k < 12; k = k + 1) {
        accm = accm + c[k] / (x + k);
    }
    
    double temp_exp = 1.0;
    for (int i = 0; i < x + 12; i = i + 1) {
        temp_exp = temp_exp * M_E;
    }
    temp_exp = 1.0 / temp_exp;
    
    double temp_pow = 1.0;
    for (int i = 0; i < x + 0.5; i = i + 1) {
        temp_pow = temp_pow * (x + 12);
    }
    
    sp_result = accm * temp_exp * temp_pow / x;
    
    return (int)(st_result + sp_result);
}
