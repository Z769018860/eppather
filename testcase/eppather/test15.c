void calculate_product(int n) {
    int i = 2;
    int product = 1;

    while (i <= n) {
        product = i * product;
        i = i + 1;
    }
}
