int fizzbuzz(int num) {
    int result[5];
    result[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (num % 3 == 0 && num % 5 == 0) {
            result[0] = 1;
        } else if (num % 3 == 0) {
            result[0] = 2;
        } else if (num % 5 == 0) {
            result[0] = 3;
        } else {
            result[0] = num;
        }
    }
    return;
}
