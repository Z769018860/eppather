int func(int n) {
    int i;
    int B[88];
    int n1;
    n1 = 100;
    for (i = 0; i < n1; i = i + 1) {
        if ((i % 3 == 0 ? 0 : 1) == 0 || (i % 5 == 0 ? 0 : 1) == 0) {
            int j;
            int k;
            k = 0;
            if (i % 3 == 0) {
                B[k] = 'F';
                k = k + 1;
                B[k] = 'i';
                k = k + 1;
                B[k] = 'z';
                k = k + 1;
                B[k] = 'z';
                k = k + 1;
            }
            if (i % 5 == 0) {
                B[k] = 'B';
                k = k + 1;
                B[k] = 'u';
                k = k + 1;
                B[k] = 'z';
                k = k + 1;
                B[k] = 'z';
                k = k + 1;
            }
            B[k] = 0;
        } else {
            int num;
            int len;
            int temp;
            num = i;
            len = 0;
            temp = num;
            while (temp != 0) {
                temp = temp / 10;
                len = len + 1;
            }
            temp = num;
            for (int j = len - 1; j >= 0; j = j - 1) {
                B[j] = '0' + (temp % 10);
                temp = temp / 10;
            }
            B[len] = 0;
        }
    }
    return;
}
