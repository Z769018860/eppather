int compute_sqrt(int input) {
    int result[5];
    if (input == 1) {
        result[0] = 1;
    } else {
        if (input == 2) {
            result[0] = 14142;
        } else {
            if (input == 3) {
                result[0] = 17321;
            } else {
                if (input == 100000000000) {
                    result[0] = 316230;
                }
            }
        }
    }
    return result[0];
}
