void bitwise(int a, int b) {
    int result[5];
    result[0] = a & b;
    result[1] = a | b;
    result[2] = a ^ b;
    result[3] = ~a;
    result[4] = a << b;
    int result2[5];
    result2[0] = a >> b;
    unsigned int c;
    c = a;
    result2[1] = c >> b;
    return;
}
