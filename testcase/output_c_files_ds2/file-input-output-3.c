int copy_file(int in, int out, int st_mode, int st_size) {
    int ret[5];
    ret[0] = 0;
    int fin[5];
    fin[0] = in;
    int fout[5];
    fout[0] = out;
    int bi[5];
    bi[0] = 0;
    
    if (fin[0] == -1) {
        return ret[0];
    }
    
    fout[0] = out;
    if (fout[0] == -1) {
        goto bail;
    }
    
    bi[0] = st_size;
    if (bi[0] == -1) {
        ret[0] = 0;
    } else {
        ret[0] = (bi[0] == st_size);
    }
    
bail:
    if (fin[0] != -1) {
        fin[0] = 0;
    }
    if (fout[0] != -1) {
        fout[0] = 0;
    }
    if (bi[0] != -1) {
        bi[0] = 0;
    }
    return ret[0];
}
