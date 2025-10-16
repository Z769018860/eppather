int is89(int x) {
    for (;;) {
        int s = 0;
        int temp = x;
        for (;;) {
            int digit = temp % 10;
            s = s + digit * digit;
            temp = temp / 10;
            if (temp == 0) {
                break;
            }
        }
        if (s == 89) {
            return 1;
        }
        if (s == 1) {
            return 0;
        }
        x = s;
    }
    return;
}
