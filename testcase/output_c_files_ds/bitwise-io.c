void b_operations(unsigned char* buf1, unsigned char* buf2) {
    int accu = 0;
    int bits = 0;
    int shift = 1;
    int n_bits = 7;
    int i;
    int j;
    int mask;
    
    for (i = 0; i < 10; i = i + 1) {
        int current_byte = buf1[i];
        int current_shift = shift;
        
        for (j = 0; j < n_bits; j = j + 1) {
            accu = (accu << 1) | (((128 >> current_shift) & current_byte) >> (7 - current_shift));
            bits = bits + 1;
            current_shift = current_shift + 1;
            if (current_shift == 8) {
                current_shift = 0;
            }
        }
        
        while (bits >= 8) {
            bits = bits - 8;
            accu = accu & ((1 << bits) - 1);
        }
    }
    
    accu = 0;
    bits = 0;
    shift = 1;
    
    for (i = 0; i < 10; i = i + 1) {
        int current_shift = shift;
        
        for (j = 0; j < n_bits; j = j + 1) {
            if (bits == 0) {
                bits = 8;
            }
            mask = 128 >> current_shift;
            if (accu & (1 << (bits - 1))) {
                buf2[i] = buf2[i] | mask;
            } else {
                buf2[i] = buf2[i] & (~mask);
            }
            bits = bits - 1;
            current_shift = current_shift + 1;
            if (current_shift >= 8) {
                current_shift = 0;
            }
        }
    }
    
    return;
}
