int invsqr(int n) {
    int result;
    result = 1;
    result = result / (n * n);
    return result;
}

void calculate_sum() {
    int sum = 0;
    int i;
    int start = 1;
    int end = 1000;
    
    for (i = start; i <= end; i = i + 1) {
        sum = sum + invsqr(i);
    }
    
    return;
}
