void doors(int n) {
    int is_open[5];
    int pass;
    int door;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        is_open[i] = 0;
    }
    
    for (pass = 0; pass < 5; pass = pass + 1) {
        for (door = pass; door < 5; door = door + pass + 1) {
            if (is_open[door] == 0) {
                is_open[door] = 1;
            } else {
                is_open[door] = 0;
            }
        }
    }
    
    return;
}
