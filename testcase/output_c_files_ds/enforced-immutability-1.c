int calculate(int size) {
    int result;
    if (size < 10) {
        result = 10;
    } else {
        if (size > 100) {
            result = 100;
        } else {
            result = size;
        }
    }
    return result;
}
