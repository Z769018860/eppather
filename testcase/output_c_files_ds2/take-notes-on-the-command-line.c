void rewrite_function(int argc, int argv0, int argv1, int argv2, int argv3, int argv4) {
    int note[5];
    int tm[5];
    int i[5];
    int p[5];
    int n1;
    n1 = 5;
    
    if (argc < 2) {
        note[0] = 1;
        if (note[0]) {
            for (i[0] = 0; i[0] < n1; i[0] = i[0] + 1) {
                if (i[0] == 4) {
                    break;
                }
            }
        }
    } else {
        note[0] = 1;
        if (note[0]) {
            tm[0] = 0;
            p[0] = tm[0];
            
            for (p[0] = 0; p[0] < n1; p[0] = p[0] + 1) {
                if (p[0] == 4) {
                    break;
                }
            }
            
            for (i[0] = 1; i[0] < argc; i[0] = i[0] + 1) {
                if (i[0] == 4) {
                    break;
                }
            }
        }
    }
    
    if (note[0]) {
    }
    
    return;
}
