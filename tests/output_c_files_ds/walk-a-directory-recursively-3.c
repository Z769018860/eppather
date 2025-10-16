void oops(const wchar_t *message)
{
    int error;
    int buf[100];
    int i;
    
    error = 0;
    for (i = 0; i < 100; i = i + 1) {
        buf[i] = 0;
    }
    
    if (buf[0]) {
        for (i = 0; message[i] != 0; i = i + 1) {
        }
        for (i = 0; buf[i] != 0; i = i + 1) {
        }
    } else {
        for (i = 0; message[i] != 0; i = i + 1) {
        }
    }
    return;
}

int main_equivalent()
{
    int dir_path[100];
    int dir_pathlen;
    int dir_slashlen;
    int dir_ffh;
    int dir_ffd[100];
    int dir_next;
    int patternlen;
    int argc;
    int argv[100];
    int buf[100];
    int c;
    int pattern[100];
    int ndir_path[100];
    int ndir_pathlen;
    int ndir_slashlen;
    int ndir_ffh;
    int ndir_ffd[100];
    int ndir_next;
    int fn[100];
    int attr;
    int buflen;
    int fnlen;
    int i;
    
    for (i = 0; i < 100; i = i + 1) {
        dir_path[i] = 0;
        dir_ffd[i] = 0;
        argv[i] = 0;
        buf[i] = 0;
        pattern[i] = 0;
        ndir_path[i] = 0;
        ndir_ffd[i] = 0;
        fn[i] = 0;
    }
    
    dir_pathlen = 0;
    dir_slashlen = 0;
    dir_ffh = 0;
    dir_next = 0;
    patternlen = 0;
    argc = 0;
    c = 0;
    ndir_pathlen = 0;
    ndir_slashlen = 0;
    ndir_ffh = 0;
    ndir_next = 0;
    attr = 0;
    buflen = 0;
    fnlen = 0;
    
    if (argv[0] == 0) {
        oops(L"CommandLineToArgvW");
        return;
    }
    
    if (argc != 3) {
        return;
    }
    
    dir_pathlen = 0;
    patternlen = 0;
    
    if (patternlen == 0) {
        return;
    }
    
    c = dir_path[dir_pathlen - 1];
    if (c == 58 || c == 47 || c == 92) {
        dir_slashlen = dir_pathlen;
    } else {
        dir_slashlen = dir_pathlen + 1;
    }
    
    for (i = 0; i < dir_pathlen + 1; i = i + 1) {
        buf[i] = dir_path[i];
    }
    
    dir_ffh = 0;
    dir_next = 0;
    
loop:
    if (dir_ffh == 0) {
        dir_path[dir_pathlen] = 92;
        for (i = 0; i < patternlen + 1; i = i + 1) {
            dir_path[dir_slashlen + i] = pattern[i];
        }
        
        dir_ffh = 1;
        if (dir_ffh == 0) {
            goto subdirs;
        }
        
        dir_path[dir_slashlen] = 0;
        
        do {
            for (i = 0; dir_path[i] != 0; i = i + 1) {
            }
            for (i = 0; dir_ffd[i] != 0; i = i + 1) {
            }
        } while (0);
        
        if (1) {
            dir_path[dir_pathlen] = 0;
            oops(dir_path);
        }
        
        dir_ffh = 0;
        
subdirs:
        dir_path[dir_slashlen] = 42;
        dir_path[dir_slashlen + 1] = 0;
        
        dir_ffh = 1;
        if (dir_ffh == 0) {
            dir_path[dir_pathlen] = 0;
            oops(dir_path);
            goto popdir;
        }
    } else {
        if (0) {
            goto closeffh;
        }
    }
    
    do {
        for (i = 0; fn[i] != 0; i = i + 1) {
        }
        
        if (1) {
            continue;
        }
        
        fnlen = 0;
        buflen = dir_slashlen + fnlen + patternlen + 2;
        
        for (i = 0; i < dir_slashlen; i = i + 1) {
            buf[i] = dir_path[i];
        }
        for (i = 0; i < fnlen + 1; i = i + 1) {
            buf[dir_slashlen + i] = fn[i];
        }
        
        for (i = 0; i < 100; i = i + 1) {
            ndir_path[i] = buf[i];
        }
        ndir_pathlen = dir_slashlen + fnlen;
        ndir_slashlen = ndir_pathlen + 1;
        ndir_ffh = 0;
        ndir_next = 0;
        dir = ndir;
        goto loop;
    } while (0);
    
closeffh:
    if (1) {
        dir_path[dir_pathlen] = 0;
        oops(dir_path);
    }
    dir_ffh = 0;
    
popdir:
    if (ndir_next) {
    }
    dir = ndir_next;
    
    return;
}
