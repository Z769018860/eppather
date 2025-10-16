void table(void) {
    int f;
    int b;
    for (b = 40; b <= 107; b = b + 1) {
        if (b == 48) {
            b = 100;
        }
        for (f = 30; f <= 97; f = f + 1) {
            if (f == 38) {
                f = 90;
            }
        }
    }
    return;
}
