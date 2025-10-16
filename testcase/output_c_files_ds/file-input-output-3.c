int copy_file(int in, int out, int size) {
    int ret = 0;
    int bi[1024];
    int i;
    int j;
    int k;
    
    for (i = 0; i < size; i = i + 1) {
        for (j = 0; j < 1024; j = j + 1) {
            if (i < size) {
                bi[j] = in;
                i = i + 1;
            } else {
                break;
            }
        }
        for (k = 0; k < j; k = k + 1) {
            out = bi[k];
        }
        if (i >= size) {
            break;
        }
    }
    
    ret = (i == size) ? 1 : 0;
    return ret;
}
