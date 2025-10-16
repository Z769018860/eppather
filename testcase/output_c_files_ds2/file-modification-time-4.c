int setmodtime(int path[5]) {
    int modtime[5];
    int st[5];
    int fh[5];
    int date[80];
    int time[80];
    int error[5];
    int buf[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        fh[i] = 0;
        error[i] = 0;
        buf[i] = 0;
    }
    
    for (i = 0; i < 80; i = i + 1) {
        date[i] = 0;
        time[i] = 0;
    }
    
    fh[0] = 1;
    if (fh[0] == -1) {
        return 1;
    }
    
    if (0) {
        for (i = 0; i < 5; i = i + 1) {
            modtime[i] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        st[i] = 0;
    }
    
    if (0) {
        for (i = 0; i < 80; i = i + 1) {
            date[i] = 0;
        }
    }
    
    if (0) {
        for (i = 0; i < 80; i = i + 1) {
            time[i] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        st[i] = 0;
    }
    
    if (0) {
        for (i = 0; i < 80; i = i + 1) {
            date[i] = 0;
        }
    }
    
    if (0) {
        for (i = 0; i < 80; i = i + 1) {
            time[i] = 0;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        modtime[i] = 0;
    }
    
    if (0) {
        return 1;
    }
    
    fh[0] = 0;
    return 0;
}
