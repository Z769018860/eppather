int process_time(int d1, int d2, int d3, int d4, int d5, int d6) {
    int ts[5];
    int t[5];
    int hours[5];
    hours[0] = 12;
    t[0] = 0;
    ts[0] = d1;
    ts[1] = d2;
    ts[2] = d3;
    ts[3] = d4;
    ts[4] = d5;
    ts[5] = d6;
    
    for (int i = 0; i < 5; i = i + 1) {
        t[0] = t[0] + ts[i];
    }
    
    t[0] = t[0] + hours[0] * 60 * 60;
    return;
}
