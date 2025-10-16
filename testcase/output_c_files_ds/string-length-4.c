int calculate_lengths(int* char_count, int* byte_count) {
    int s[4] = {0x304A, 0x306F, 0x3088, 0x3046};
    int length = 0;
    
    for (int i = 0; i < 4; i = i + 1) {
        if (s[i] != 0) {
            length = length + 1;
        }
    }
    
    *char_count = length;
    *byte_count = 4 * 2;
    return;
}
