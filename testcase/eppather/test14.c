void process(int a, int b, int c, int d, int e) {
    while (a != b) {
        b = b + 1;
        c = a % b;

        if (c == 0) {
            d = d + 1;
            e = e + b;
        }
        ;
    }
}
