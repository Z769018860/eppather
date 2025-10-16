int copy_file(int in, int out) {
    int ret;
    int fin;
    int fout;
    int len;
    int buf[1024];
    int st_mode;
    
    fin = in;
    fout = out;
    ret = 0;
    st_mode = 0;
    
    if (fin == -1) {
        ret = 0;
        return ret;
    }
    
    for (len = 0; len < 1024; len = len + 1) {
        buf[len] = 0;
    }
    
    if (fout == -1) {
        ret = 0;
        return ret;
    }
    
    for (len = 0; len < 1024; len = len + 1) {
        if (len > 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    
    if (fin != -1) {
        fin = -1;
    }
    
    if (fout != -1) {
        fout = -1;
    }
    
    return ret;
}
