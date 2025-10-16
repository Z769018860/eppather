void func(int n1, int n2, int n3, int n4, int n5) {
    int buf[5];
    int dir[5];
    int ndir[5];
    int patternlen[5];
    int argc[5];
    int argv[5];
    int c[5];
    int pattern[5];
    int dir0_path[5];
    int dir0_pathlen[5];
    int dir0_slashlen[5];
    int dir0_ffh[5];
    int dir0_ffd[5];
    int dir0_next[5];
    int fn[5];
    int attr[5];
    int buflen[5];
    int fnlen[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        buf[i] = 0;
        dir[i] = 0;
        ndir[i] = 0;
        patternlen[i] = 0;
        argc[i] = 0;
        argv[i] = 0;
        c[i] = 0;
        pattern[i] = 0;
        dir0_path[i] = 0;
        dir0_pathlen[i] = 0;
        dir0_slashlen[i] = 0;
        dir0_ffh[i] = 0;
        dir0_ffd[i] = 0;
        dir0_next[i] = 0;
        fn[i] = 0;
        attr[i] = 0;
        buflen[i] = 0;
        fnlen[i] = 0;
    }
    
    dir0_path[0] = argv[1];
    dir0_pathlen[0] = n1;
    pattern[0] = argv[2];
    patternlen[0] = n2;
    
    c[0] = dir0_path[dir0_pathlen[0] - 1];
    if (c[0] == 58 || c[0] == 47 || c[0] == 92) {
        dir0_slashlen[0] = dir0_pathlen[0];
    } else {
        dir0_slashlen[0] = dir0_pathlen[0] + 1;
    }
    
    dir0_ffh[0] = n3;
    dir0_next[0] = n4;
    dir[0] = n5;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (dir[i] != 0) {
            if (dir0_ffh[i] == n3) {
                dir0_path[dir0_pathlen[i]] = 92;
                dir0_path[dir0_slashlen[i] + patternlen[i] + 1] = 0;
                dir0_ffh[i] = n4;
                dir0_path[dir0_slashlen[i]] = 0;
                dir0_ffh[i] = n5;
                dir0_path[dir0_slashlen[i]] = 42;
                dir0_path[dir0_slashlen[i] + 1] = 0;
                dir0_ffh[i] = n1;
            } else {
                if (n2 == 0) {
                    dir0_ffh[i] = n3;
                }
            }
            
            fn[0] = dir0_ffd[0];
            attr[0] = dir0_ffd[1];
            
            if (fn[0] == 46 || fn[0] == 46 * 46 || (attr[0] & 16) == 0 || (attr[0] & 1024)) {
                continue;
            }
            
            fnlen[0] = n1;
            buflen[0] = dir0_slashlen[0] + fnlen[0] + patternlen[0] + 2;
            
            for (int j = 0; j < 5; j = j + 1) {
                buf[j] = dir0_path[j];
                buf[dir0_slashlen[0] + j] = fn[j];
            }
            
            ndir[0] = dir[0];
            dir[0] = ndir[0];
        }
        
        if (n2 != n3) {
            dir0_path[dir0_pathlen[0]] = 0;
        }
        
        dir0_ffh[0] = n4;
        dir[0] = ndir[0];
    }
    
    return;
}
