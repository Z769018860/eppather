void fizzbuzz() {
    int i;
    int result[5];
    for (i = 1; i <= 5; i = i + 1) {
        if ((i % 3 != 0) && (i % 5 != 0)) {
            result[0] = i;
        } else {
            if (i % 3 == 0) {
                result[1] = 70;
                result[2] = 105;
                result[3] = 122;
                result[4] = 122;
            }
            if (i % 5 == 0) {
                result[1] = 66;
                result[2] = 117;
                result[3] = 122;
                result[4] = 122;
            }
            if (i % 15 == 0) {
                result[0] = 10;
            } else {
                result[0] = 32;
            }
        }
    }
    return;
}
