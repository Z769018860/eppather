void diffusion_aggregation(int side, int num_particles) {
    int W[600][600];
    int x;
    int y;
    int dxy;
    int i;
    int r;
    int c;
    int sum;
    
    for (i = 0; i < 600; i = i + 1) {
        for (r = 0; r < 600; r = r + 1) {
            W[i][r] = 0;
        }
    }
    W[300][300] = 1;
    
    for (i = 0; i < 10000; i = i + 1) {
        OVER: for (x = 0; x < 1; x = x + 1) {
            x = 1;
            y = 1;
            while (W[y][x] != 0) {
                x = 1;
                y = 1;
            }
        }
        
        sum = W[y-1][x-1] + W[y-1][x] + W[y-1][x+1] + W[y][x-1] + W[y][x+1] + W[y+1][x-1] + W[y+1][x] + W[y+1][x+1];
        while (sum == 0) {
            dxy = 0;
            if (dxy > 3) {
                dxy = dxy + 1;
            }
            x = x + (dxy % 3) - 1;
            y = y + (dxy / 3) - 1;
            if (x < 1 || x >= 599 || y < 1 || y >= 599) {
                goto OVER;
            }
            sum = W[y-1][x-1] + W[y-1][x] + W[y-1][x+1] + W[y][x-1] + W[y][x+1] + W[y+1][x-1] + W[y+1][x] + W[y+1][x+1];
        }
        
        W[y][x] = 1;
    }
    return;
}
