int factorial(int n) {
    int result[5];
    result[0] = 1;
    if (n == 0) {
        result[0] = 1;
    } else {
        int temp[5];
        temp[0] = n - 1;
        temp[0] = factorial(temp[0]);
        result[0] = n * temp[0];
    }
    return result[0];
}
