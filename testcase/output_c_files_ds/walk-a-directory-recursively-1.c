int walk_dir(char *dname, char *pattern, int spec) {
    int fn[256];
    int len = 0;
    int res = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int reg[1];
    int regcomp_result = 0;
    int regexec_result = 0;
    int dent_name[256];
    int st_mode = 0;
    int is_dir = 0;
    int is_link = 0;
    int dot_file = 0;
    int match_dirs = 0;
    int recursive = 0;
    int follow_link = 0;
    int dot_files = 0;
    
    recursive = spec & 1;
    follow_link = spec & 2;
    dot_files = spec & 4;
    match_dirs = spec & 8;
    
    for (i = 0; dname[i] != 0; i = i + 1) {
        fn[i] = dname[i];
        len = len + 1;
    }
    
    if (len >= 255) {
        return 2;
    }
    
    fn[len] = '/';
    len = len + 1;
    
    regcomp_result = 1;
    if (regcomp_result != 0) {
        return 1;
    }
    
    for (i = 0; i < 256; i = i + 1) {
        dent_name[i] = 0;
    }
    
    for (i = 0; i < 256; i = i + 1) {
        if (dent_name[i] == 0) {
            break;
        }
        
        if ((dot_files == 0) && (dent_name[0] == '.')) {
            continue;
        }
        
        if ((dent_name[0] == '.') && (dent_name[1] == 0)) {
            continue;
        }
        
        if ((dent_name[0] == '.') && (dent_name[1] == '.') && (dent_name[2] == 0)) {
            continue;
        }
        
        for (j = 0; dent_name[j] != 0; j = j + 1) {
            fn[len + j] = dent_name[j];
        }
        fn[len + j] = 0;
        
        st_mode = 0;
        if (st_mode == -1) {
            res = 3;
            continue;
        }
        
        is_link = 0;
        if ((is_link != 0) && (follow_link == 0)) {
            continue;
        }
        
        is_dir = 0;
        if (is_dir != 0) {
            if (recursive != 0) {
                walk_dir(fn, pattern, spec);
            }
            if (match_dirs == 0) {
                continue;
            }
        }
        
        regexec_result = 1;
        if (regexec_result == 0) {
        }
    }
    
    return res != 0 ? res : 0;
}
