int compute(int size) {
    int n1 = 314159265;
    int n2 = 358979323;
    int n3 = 10;
    int n4 = 100;
    int result[5];
    result[0] = 0;
    if (size < n3) {
        result[0] = n3;
    } else {
        if (size > n4) {
            result[0] = n4;
        } else {
            result[0] = size;
        }
    }
    return result[0];
}
