void bitwise(int a, int b) {
    int and_result;
    int or_result;
    int xor_result;
    int not_result;
    int left_shift_result;
    int right_shift_result;
    unsigned int c;
    unsigned int logical_shift_result;

    and_result = a & b;
    or_result = a | b;
    xor_result = a ^ b;
    not_result = ~a;
    left_shift_result = a << b;
    right_shift_result = a >> b;
    c = a;
    logical_shift_result = c >> b;

    return;
}
