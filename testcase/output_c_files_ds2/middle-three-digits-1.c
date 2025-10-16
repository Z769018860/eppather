int mid3(int n, char* buf, int buf_len) {
    int abs_n = n;
    if (n < 0) {
        abs_n = -n;
    }
    
    int l = 0;
    int temp = abs_n;
    for (int i = 0; i < 5; i = i + 1) {
        if (temp == 0) {
            break;
        }
        temp = temp / 10;
        l = l + 1;
    }
    
    if (l < 3 || (l % 2) == 0) {
        return 0;
    }
    
    int mid_pos = l / 2 - 1;
    for (int i = 0; i < 3; i = i + 1) {
        int digit = abs_n;
        for (int j = 0; j < l - mid_pos - i - 1; j = j + 1) {
            digit = digit / 10;
        }
        buf[i] = (digit % 10) + 48;
    }
    buf[3] = 0;
    return 1;
}
