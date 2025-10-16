int fib(int n) {
    int phi_numerator[5];
    phi_numerator[0] = 1;
    int phi_denominator[5];
    phi_denominator[0] = 2;
    int sqrt5[5];
    sqrt5[0] = 2;
    int result[5];
    result[0] = 0;
    int i;
    int power1[5];
    power1[0] = 1;
    int power2[5];
    power2[0] = 1;
    int temp[5];
    temp[0] = 1;
    
    for (i = 0; i < 5; i = i + 1) {
        power1[0] = power1[0] * (phi_numerator[0] + sqrt5[0]) / phi_denominator[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[0] = 1 - (phi_numerator[0] + sqrt5[0]) / phi_denominator[0];
        power2[0] = power2[0] * temp[0];
    }
    
    result[0] = (power1[0] - power2[0]) / sqrt5[0];
    return result[0];
}
