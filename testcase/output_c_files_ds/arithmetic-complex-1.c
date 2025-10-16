void complex_operations() {
    double a_real = 1.0;
    double a_imag = 1.0;
    double b_real = 3.14159;
    double b_imag = 1.2;
    double c_real;
    double c_imag;
    
    c_real = a_real + b_real;
    c_imag = a_imag + b_imag;
    
    c_real = a_real * b_real - a_imag * b_imag;
    c_imag = a_real * b_imag + a_imag * b_real;
    
    double denom = a_real * a_real + a_imag * a_imag;
    c_real = a_real / denom;
    c_imag = -a_imag / denom;
    
    c_real = -a_real;
    c_imag = -a_imag;
    
    c_real = a_real;
    c_imag = -a_imag;
    
    return;
}
