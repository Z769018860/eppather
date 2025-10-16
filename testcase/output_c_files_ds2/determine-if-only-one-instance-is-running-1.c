void only_one_instance(int dirlen, int fd, int fl_start, int fl_len, int fl_type, int fl_whence) {
    int ooi_path[5];
    int dir[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        dir[i] = 0;
        ooi_path[i] = 0;
    }
    
    if (dir[0] == 0 || dir[0] != 47) {
        return;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ooi_path[i] = dir[i];
    }
    
    if (fd < 0) {
        return;
    }
    
    fl_start = 0;
    fl_len = 0;
    fl_type = 2;
    fl_whence = 0;
    
    if (fd < 0) {
        return;
    }
    
    return;
}
