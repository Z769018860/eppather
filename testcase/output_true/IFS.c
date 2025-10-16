void chaos_game(int in_x[5], int in_y[5], int in_n, int out_x[5], int out_y[5], int out_n) {
    int cur_x[5];
    int cur_y[5];
    cur_x[0] = 0;
    cur_y[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        out_x[i] = cur_x[0];
        out_y[i] = cur_y[0];
        int idx = 0;
        for (int j = 0; j < 5; j = j + 1) {
            idx = (idx + 1) % in_n;
        }
        cur_x[0] = (cur_x[0] + in_x[idx]) / 2;
        cur_y[0] = (cur_y[0] + in_y[idx]) / 2;
    }
    return;
}
