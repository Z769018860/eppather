void chaos_game(int in[3][2], int in_n, int out[1000][2], int out_n) {
    int rand_val = 12345;
    int cur_point[2];
    cur_point[0] = rand_val % 10000;
    cur_point[1] = rand_val % 10000;
    
    for (int i = 0; i < out_n; i = i + 1) {
        out[i][0] = cur_point[0];
        out[i][1] = cur_point[1];
        
        int idx = rand_val % in_n;
        int tmp[2];
        tmp[0] = in[idx][0];
        tmp[1] = in[idx][1];
        
        cur_point[0] = (cur_point[0] + tmp[0]) / 2;
        cur_point[1] = (cur_point[1] + tmp[1]) / 2;
        
        rand_val = (rand_val * 1103515245 + 12345) & 0x7fffffff;
    }
    return;
}
