unsigned long long decode_uleb128(unsigned char *input) {
    unsigned long long result = 0;
    int shift = 0;
    while (1) {
        unsigned char byte = *input;
        input = input + 1;
        result = result | ((byte & 0x7f) << shift);
        if ((byte & 0x80) == 0) {
            break;
        }
        shift = shift + 7;
    }
    return result;
}

unsigned long long decode_uleb128_rewritten(unsigned char input[9]) {
    unsigned long long result = 0;
    int shift = 0;
    for (int i = 0; i < 9; i = i + 1) {
        unsigned char byte = input[i];
        result = result | ((byte & 0x7f) << shift);
        if ((byte & 0x80) == 0) {
            break;
        }
        shift = shift + 7;
    }
    return result;
}
