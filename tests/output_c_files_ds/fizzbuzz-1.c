void fizzbuzz() {
    int i = 0;
    char B[88];
    int temp;
    for (i = 0; i < 100; i = i + 1) {
        temp = 0;
        if (i % 3 == 0) {
            B[0] = 'F';
            B[1] = 'i';
            B[2] = 'z';
            B[3] = 'z';
            B[4] = '\0';
            temp = 1;
        } else {
            B[0] = '\0';
        }
        if (i % 5 == 0) {
            if (temp == 1) {
                B[4] = 'B';
                B[5] = 'u';
                B[6] = 'z';
                B[7] = 'z';
                B[8] = '\0';
            } else {
                B[0] = 'B';
                B[1] = 'u';
                B[2] = 'z';
                B[3] = 'z';
                B[4] = '\0';
            }
            temp = 1;
        }
        if (temp == 0) {
            int num = i + 1;
            int digits = 0;
            int n = num;
            while (n != 0) {
                n = n / 10;
                digits = digits + 1;
            }
            n = num;
            for (int j = digits - 1; j >= 0; j = j - 1) {
                B[j] = '0' + (n % 10);
                n = n / 10;
            }
            B[digits] = '\0';
        }
    }
    return;
}
