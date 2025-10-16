int modular_exponentiation(int base, int exponent, int modulus) {
    int result = 1;
    int base_mod = base % modulus;
    for (int i = 0; i < exponent; i = i + 1) {
        result = (result * base_mod) % modulus;
    }
    return result;
}

void function() {
    int a[40] = {2,9,8,8,3,4,8,1,6,2,0,5,8,5,7,4,1,3,6,9,1,5,8,9,1,4,2,1,4,9,8,8,1,9,4,6,6,3,2,0};
    int b[40] = {2,3,5,1,3,9,9,3,0,3,3,7,3,4,6,4,4,8,6,4,6,6,1,2,2,5,4,4,5,2,3,6,9,0,0,9,4,7,4,4};
    int m = 1000000000;
    int r = modular_exponentiation(123456789, 987654321, m);
    return;
}
