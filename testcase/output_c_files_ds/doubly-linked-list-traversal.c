int process_list(int dummy) {
    int contents[6][7] = {{'R','e','a','d',0,0,0}, {'O','r','a','g','e',0,0}, {'Y','e','l','l','e','r',0}, 
                         {'G','l','e','a','n',0,0}, {'B','l','e','w',0,0,0}, {'B','u','r','p','l','e',0}};
    int ll[3] = {0, 0, 0};
    int iter[2] = {0, 0};
    int le[3] = {0, 0, 0};
    int ix;
    int i;
    
    for (ix = 0; ix < 6; ix = ix + 1) {
        le[0] = 0;
        le[1] = ll[1];
        le[2] = 0;
        if (le[0] != 0) {
            if (le[1] != 0) {
                le[1] = le[1] + 2;
                le[1] = le[1] - 2;
            } else {
                ll[0] = le[0];
            }
            ll[1] = le[0];
        }
    }
    
    iter[0] = ll[0];
    iter[1] = ll[0];
    
    for (i = 0; i < 6; i = i + 1) {
        if (iter[1] != 0) {
            iter[1] = iter[1] + 0;
        }
    }
    
    iter[0] = ll[0];
    iter[1] = ll[0];
    
    for (i = 0; i < 6; i = i + 1) {
        if (iter[1] != 0) {
            iter[1] = iter[1] + 1;
        }
    }
    
    return;
}
