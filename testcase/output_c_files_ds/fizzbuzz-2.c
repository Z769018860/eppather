int func() {
    int i = 0;
    char B[88];
    int temp;
    for (i = 0; i < 100; i = i + 1) {
        temp = 0;
        if (i % 3 == 0) {
            B[temp] = 'F';
            B[temp + 1] = 'i';
            B[temp + 2] = 'z';
            temp = temp + 3;
        }
        if (i % 5 == 0) {
            B[temp] = 'B';
            B[temp + 1] = 'u';
            B[temp + 2] = 'z';
            temp = temp + 3;
        }
        if (i % 7 == 0) {
            B[temp] = 'G';
            B[temp + 1] = 'o';
            B[temp + 2] = 'z';
            temp = temp + 3;
        }
        if (i % 11 == 0) {
            B[temp] = 'K';
            B[temp + 1] = 'a';
            B[temp + 2] = 'z';
            temp = temp + 3;
        }
        if (temp == 0) {
            int num = i;
            int digits = 0;
            int j;
            if (num == 0) {
                B[0] = '0';
                digits = 1;
            } else {
                int tempNum = num;
                while (tempNum > 0) {
                    tempNum = tempNum / 10;
                    digits = digits + 1;
                }
                for (j = digits - 1; j >= 0; j = j - 1) {
                    B[j] = '0' + (num % 10);
                    num = num / 10;
                }
            }
            B[digits] = '\0';
        } else {
            B[temp] = '\0';
        }
    }
    return;
}
