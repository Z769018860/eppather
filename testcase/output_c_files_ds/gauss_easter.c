int computus(int year, int servois) {
    int a = year % 19;
    int k = year / 100;
    int p = (13 + 8 * k) / 25;
    int q = k / 4;
    int M = (15 - p + k - q) % 30;
    int d = (19 * a + M) % 30;
    
    if (servois != 0) {
        return (21 + d) % 31;
    }
    
    int N = (4 + k - q) % 7;
    int b = year % 4;
    int c = year % 7;
    int e = (2 * b + 4 * c + 6 * d + N) % 7;
    
    if ((d == 29 && e == 6) || (d == 28 && e == 6 && a > 10)) {
        e = -1;
    }
    
    if ((22 + d + e) > 31) {
        return 400 + d + e - 9;
    } else {
        return 300 + 22 + d + e;
    }
    
    return 0;
}
