int only_one_instance() {
    int fl[4];
    int dirlen;
    int fd;
    char dir[256];
    char ooi_path[256];
    int i;
    int j;
    
    for (i = 0; i < 256; i = i + 1) {
        dir[i] = 0;
        ooi_path[i] = 0;
    }
    
    dir[0] = '/';
    dir[1] = 'h';
    dir[2] = 'o';
    dir[3] = 'm';
    dir[4] = 'e';
    dirlen = 5;
    
    for (i = 0; i < dirlen; i = i + 1) {
        ooi_path[i] = dir[i];
    }
    
    ooi_path[dirlen] = '/';
    ooi_path[dirlen + 1] = 'r';
    ooi_path[dirlen + 2] = 'o';
    ooi_path[dirlen + 3] = 's';
    ooi_path[dirlen + 4] = 'e';
    ooi_path[dirlen + 5] = 't';
    ooi_path[dirlen + 6] = 't';
    ooi_path[dirlen + 7] = 'a';
    ooi_path[dirlen + 8] = '-';
    ooi_path[dirlen + 9] = 'c';
    ooi_path[dirlen + 10] = 'o';
    ooi_path[dirlen + 11] = 'd';
    ooi_path[dirlen + 12] = 'e';
    ooi_path[dirlen + 13] = '-';
    ooi_path[dirlen + 14] = 'l';
    ooi_path[dirlen + 15] = 'o';
    ooi_path[dirlen + 16] = 'c';
    ooi_path[dirlen + 17] = 'k';
    ooi_path[dirlen + 18] = 0;
    
    fl[0] = 0;
    fl[1] = 0;
    fl[2] = 1;
    fl[3] = 0;
    
    fd = 1;
    
    if (fd < 0) {
        return 1;
    }
    
    if (1 < 0) {
        return 1;
    }
    
    return 0;
}
