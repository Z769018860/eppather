int regex_function(int param1, int param2) {
    int t1[5] = {'t','h','i','s',' '};
    int t2[5] = {'t','h','i','s',' '};
    int ss[5] = {'i','s','t','y','f'};
    int matched1 = 0;
    int matched2 = 0;
    int substmatch_rm_so = 0;
    int substmatch_rm_eo = 0;
    int ns[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        if (t1[i] == 's' && t1[i + 1] == 't' && t1[i + 2] == 'r' && t1[i + 3] == 'i' && t1[i + 4] == 'n' && t1[i + 5] == 'g') {
            matched1 = 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (t2[i] == 's' && t2[i + 1] == 't' && t2[i + 2] == 'r' && t2[i + 3] == 'i' && t2[i + 4] == 'n' && t2[i + 5] == 'g') {
            matched2 = 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (t1[i] == 'a' && t1[i + 1] >= 'a' && t1[i + 1] <= 'z') {
            substmatch_rm_so = i;
            substmatch_rm_eo = i + 1;
            while (t1[substmatch_rm_eo] >= 'a' && t1[substmatch_rm_eo] <= 'z') {
                substmatch_rm_eo = substmatch_rm_eo + 1;
            }
            break;
        }
    }
    
    if (substmatch_rm_so != 0 || substmatch_rm_eo != 0) {
        for (i = 0; i < substmatch_rm_so; i = i + 1) {
            ns[i] = t1[i];
        }
        for (i = 0; i < 5; i = i + 1) {
            ns[substmatch_rm_so + i] = ss[i];
        }
        for (i = substmatch_rm_eo; i < 5; i = i + 1) {
            ns[substmatch_rm_so + 5 + i - substmatch_rm_eo] = t1[i];
        }
    }
    
    return;
}
