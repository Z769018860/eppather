int parse_numbers(int num1, int num2, int num3) {
    int num[5];
    num[0] = 123459;
    num[1] = 180154659;
    num[2] = 4009;
    num[3] = 0;
    num[4] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (i == 0) {
            num[0] = num1;
        } else if (i == 1) {
            num[1] = num2;
        } else if (i == 2) {
            num[2] = num3;
        }
    }
    return;
}
