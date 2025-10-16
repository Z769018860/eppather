void diffusionLimitedAggregation() {
    int W[600][600];
    int x;
    int y;
    int dxy;
    int i;
    int r;
    int c;
    int sum;
    int SIDE;
    int NUM_PARTICLES;
    
    SIDE = 600;
    NUM_PARTICLES = 10000;
    
    for (r = 0; r < SIDE; r = r + 1) {
        for (c = 0; c < SIDE; c = c + 1) {
            W[r][c] = 0;
        }
    }
    
    W[SIDE / 2][SIDE / 2] = 1;
    
    for (i = 0; i < NUM_PARTICLES; i = i + 1) {
        OVER: while (1) {
            x = 1 + (i * 7919) % (SIDE - 2);
            y = 1 + (i * 65537) % (SIDE - 2);
            if (W[y][x] == 0) {
                break;
            }
        }
        
        while (1) {
            sum = W[y-1][x-1] + W[y-1][x] + W[y-1][x+1] + W[y][x-1] + W[y][x+1] + W[y+1][x-1] + W[y+1][x] + W[y+1][x+1];
            if (sum != 0) {
                break;
            }
            
            dxy = (i * 100003) % 8;
            if (dxy > 3) {
                dxy = dxy + 1;
            }
            x = x + (dxy % 3) - 1;
            y = y + (dxy / 3) - 1;
            
            if (x < 1 || x >= SIDE - 1 || y < 1 || y >= SIDE - 1) {
                goto OVER;
            }
        }
        
        W[y][x] = 1;
    }
    
    return;
}
