void complex_ops(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20) {
    int a_real[5];
    int a_imag[5];
    int b_real[5];
    int b_imag[5];
    int ans_real[5];
    int ans_imag[5];
    int denom[5];
    int i;
    
    a_real[0] = 1;
    a_imag[0] = 1;
    b_real[0] = 3;
    b_imag[0] = 1;
    
    for (i = 0; i < 5; i = i + 1) {
        ans_real[0] = a_real[0] + b_real[0];
        ans_imag[0] = a_imag[0] + b_imag[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ans_real[0] = a_real[0] * b_real[0] - a_imag[0] * b_imag[0];
        ans_imag[0] = a_real[0] * b_imag[0] + a_imag[0] * b_real[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        denom[0] = a_real[0] * a_real[0] + a_imag[0] * a_imag[0];
        ans_real[0] = a_real[0] / denom[0];
        ans_imag[0] = -a_imag[0] / denom[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ans_real[0] = -a_real[0];
        ans_imag[0] = -a_imag[0];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ans_real[0] = a_real[0];
        ans_imag[0] = -a_imag[0];
    }
    
    return;
}
