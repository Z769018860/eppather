int func() {
    int is_open[100];
    int pass;
    int door;
    int i;
    
    for (i = 0; i < 100; i = i + 1) {
        is_open[i] = 0;
    }
    
    for (pass = 0; pass < 100; pass = pass + 1) {
        for (door = pass; door < 100; door = door + pass + 1) {
            if (is_open[door] == 0) {
                is_open[door] = 1;
            } else {
                is_open[door] = 0;
            }
        }
    }
    
    return;
}
