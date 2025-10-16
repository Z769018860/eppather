void roots_quadratic_eq(int a, int b, int c, int x[2]) {
    int delta_real;
    int delta_imag;
    int sqrt_delta_real;
    int sqrt_delta_imag;
    int denominator;
    int temp_real;
    int temp_imag;
    
    delta_real = b * b - 4 * a * c;
    delta_imag = 0;
    
    if (delta_real >= 0) {
        sqrt_delta_real = 1;
        while (sqrt_delta_real * sqrt_delta_real <= delta_real) {
            sqrt_delta_real = sqrt_delta_real + 1;
        }
        sqrt_delta_real = sqrt_delta_real - 1;
        sqrt_delta_imag = 0;
    } else {
        sqrt_delta_real = 0;
        sqrt_delta_imag = 1;
        while (sqrt_delta_imag * sqrt_delta_imag <= -delta_real) {
            sqrt_delta_imag = sqrt_delta_imag + 1;
        }
        sqrt_delta_imag = sqrt_delta_imag - 1;
    }
    
    denominator = 2 * a;
    
    temp_real = -b + sqrt_delta_real;
    temp_imag = sqrt_delta_imag;
    x[0] = temp_real / denominator;
    x[2] = temp_imag / denominator;
    
    temp_real = -b - sqrt_delta_real;
    temp_imag = -sqrt_delta_imag;
    x[1] = temp_real / denominator;
    x[3] = temp_imag / denominator;
    
    return;
}
