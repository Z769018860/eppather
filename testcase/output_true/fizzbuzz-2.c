int func(int n) {
    int i;
    int B[88];
    int result[5];
    result[0] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        B[0] = 0;
        if ((i + 1) % 3 == 0) {
            B[0] = 'F';
            B[1] = 'i';
            B[2] = 'z';
            B[3] = 0;
        }
        if ((i + 1) % 5 == 0) {
            B[0] = 'B';
            B[1] = 'u';
            B[2] = 'z';
            B[3] = 0;
        }
        if ((i + 1) % 7 == 0) {
            B[0] = 'G';
            B[1] = 'o';
            B[2] = 'z';
            B[3] = 0;
        }
        if ((i + 1) % 11 == 0) {
            B[0] = 'K';
            B[1] = 'a';
            B[2] = 'z';
            B[3] = 0;
        }
        if (B[0] == 0) {
            int temp = i + 1;
            int digits = 0;
            int temp2 = temp;
            while (temp2 > 0) {
                temp2 = temp2 / 10;
                digits = digits + 1;
            }
            temp2 = temp;
            for (int j = digits - 1; j >= 0; j = j - 1) {
                B[j] = '0' + (temp2 % 10);
                temp2 = temp2 / 10;
            }
            B[digits] = 0;
        }
        result[0] = result[0] + 1;
    }
    return;
}
