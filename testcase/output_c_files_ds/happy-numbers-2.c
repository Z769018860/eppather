int happy(int n) {
    int sum;
    int x;
    int nn;
    for (; n > 999;) {
        sum = 0;
        for (; n; n = n / 10) {
            x = n % 10;
            sum = sum + x * x;
        }
        n = sum;
    }
    sum = 0;
    for (; n; n = n / 10) {
        x = n % 10;
        sum = sum + x * x;
    }
    nn = sum;
    for (; nn != n && nn != 1;) {
        sum = 0;
        for (; n; n = n / 10) {
            x = n % 10;
            sum = sum + x * x;
        }
        n = sum;
        sum = 0;
        for (; nn; nn = nn / 10) {
            x = nn % 10;
            sum = sum + x * x;
        }
        nn = sum;
        sum = 0;
        for (; nn; nn = nn / 10) {
            x = nn % 10;
            sum = sum + x * x;
        }
        nn = sum;
    }
    if (n == 1) {
        return 1;
    } else {
        return 0;
    }
    return;
}
