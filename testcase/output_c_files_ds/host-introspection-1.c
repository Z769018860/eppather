int check_endian() {
    int one = 1;
    int result = 0;
    char* ptr = (char*)&one;
    if (*ptr != 0) {
        result = 1;
    }
    else {
        result = 0;
    }
    return result;
}
