int factorialSafe(int n) {
    int result;
    if (n < 0) {
        result = -1;
    } else {
        if (n == 0) {
            result = 1;
        } else {
            int temp = n - 1;
            int temp_result = factorialSafe(temp);
            result = n * temp_result;
        }
    }
    return result;
}
