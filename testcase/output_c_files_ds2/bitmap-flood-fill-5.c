void floodfill_func(int x, int y, int ic_red, int ic_green, int ic_blue, int rc_red, int rc_green, int rc_blue) {
    int animage[5];
    int ic[3];
    int rc[3];
    
    ic[0] = 255;
    ic[1] = 255;
    ic[2] = 255;
    rc[0] = 0;
    rc[1] = 255;
    rc[2] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        animage[i] = 0;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (animage[i] == ic[0]) {
            animage[i] = rc[0];
        }
    }
    
    return;
}
