int factorial(int x) {
    int result = 1;
    for (int i = 1; i <= x; i = i + 1) {
        result = result * i;
    }
    return result;
}
