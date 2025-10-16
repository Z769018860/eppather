int detect_endianness(int n) {
    int one[5];
    one[0] = 1;
    int result[5];
    result[0] = 0;
    
    if (*(char *)&one[0]) {
        result[0] = 1;
    } else {
        result[0] = 0;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        one[i] = 0;
    }
    
    return result[0];
}
