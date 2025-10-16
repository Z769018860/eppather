unsigned int fib(unsigned int n) {
    int phi_num = 1618034;
    int phi_den = 1000000;
    int sqrt5_num = 2236068;
    int sqrt5_den = 1000000;
    int pow_phi_n_num = 1;
    int pow_phi_n_den = 1;
    int pow_1mphi_n_num = 1;
    int pow_1mphi_n_den = 1;
    int temp_num;
    int temp_den;
    int result_num;
    int result_den;
    int i;

    for (i = 0; i < n; i = i + 1) {
        temp_num = pow_phi_n_num * phi_num;
        temp_den = pow_phi_n_den * phi_den;
        pow_phi_n_num = temp_num;
        pow_phi_n_den = temp_den;
    }

    for (i = 0; i < n; i = i + 1) {
        temp_num = pow_1mphi_n_num * (1000000 - phi_num);
        temp_den = pow_1mphi_n_den * phi_den;
        pow_1mphi_n_num = temp_num;
        pow_1mphi_n_den = temp_den;
    }

    result_num = pow_phi_n_num * pow_1mphi_n_den - pow_1mphi_n_num * pow_phi_n_den;
    result_den = pow_phi_n_den * pow_1mphi_n_den;
    result_num = result_num * sqrt5_den;
    result_den = result_den * sqrt5_num;

    return (unsigned int)(result_num / result_den);
}
