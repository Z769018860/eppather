int dir_empty(int path_len, int d_name_len) {
    int ent[5];
    int ret[5];
    ret[0] = 1;
    int d[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        ent[i] = 0;
    }
    
    d[0] = 0;
    if (d[0] == 0) {
        return -1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (ent[0] == 0) {
            continue;
        }
        if (ent[0] == 1) {
            continue;
        }
        ret[0] = 0;
        break;
    }
    
    d[0] = 0;
    return ret[0];
    return;
}
