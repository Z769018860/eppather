char* bin(unsigned int x) {
    unsigned int bits;
    unsigned int temp;
    char ret[33];
    unsigned int i;
    
    if (x == 0) {
        bits = 1;
    } else {
        temp = x;
        bits = 0;
        while (temp != 0) {
            temp = temp / 2;
            bits = bits + 1;
        }
    }
    
    for (i = 0; i < bits; i = i + 1) {
        ret[bits - i - 1] = (x & 1) ? '1' : '0';
        x = x >> 1;
    }
    ret[bits] = '\0';
    
    return ret;
}
