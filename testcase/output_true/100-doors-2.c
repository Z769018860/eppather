int func(int n) {
    int is_open[100];
    int doorptr;
    int doorlimit;
    int pass;
    int i;
    
    for (i = 0; i < 100; i = i + 1) {
        is_open[i] = 0;
    }
    
    doorlimit = 100;
    
    for (pass = 100; pass; pass = pass - 1) {
        for (doorptr = pass - 1; doorptr < doorlimit; doorptr = doorptr + pass) {
            is_open[doorptr] = is_open[doorptr] ^ 1;
        }
    }
    
    return;
}
