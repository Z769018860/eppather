int grep(int in[10], int out[10], int len, int inplace, int sel_type) {
    int i;
    int j;
    int temp[10];
    
    for (i = 0; i < 10; i = i + 1) {
        temp[i] = in[i];
    }
    
    j = 0;
    for (i = 0; i < len; i = i + 1) {
        if (sel_type == 0) {
            if ((temp[i] & 1) == 0) {
                if (inplace == 0) {
                    out[j] = temp[i];
                } else {
                    in[j] = temp[i];
                }
                j = j + 1;
            }
        } else {
            if ((temp[i] % 3) != 0) {
                if (inplace == 0) {
                    out[j] = temp[i];
                } else {
                    in[j] = temp[i];
                }
                j = j + 1;
            }
        }
    }
    
    return j;
}
