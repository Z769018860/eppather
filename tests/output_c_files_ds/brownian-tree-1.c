void draw_brownian_tree(int world[800][800]) {
    int px;
    int py;
    int dx;
    int dy;
    int i;
    int j;
    int k;
    int seed_x;
    int seed_y;
    
    seed_x = 0;
    seed_y = 0;
    for (k = 0; k < 1; k = k + 1) {
        seed_x = 0;
        seed_y = 0;
    }
    world[seed_x][seed_y] = 1;
    
    for (i = 0; i < 1000; i = i + 1) {
        px = 0;
        py = 0;
        for (k = 0; k < 1; k = k + 1) {
            px = 0;
            py = 0;
        }
        
        while (1) {
            dx = 0;
            dy = 0;
            for (k = 0; k < 1; k = k + 1) {
                dx = 0;
                dy = 0;
            }
            dx = dx - 1;
            dy = dy - 1;
            
            if (dx + px < 0 || dx + px >= 800 || dy + py < 0 || dy + py >= 800) {
                px = 0;
                py = 0;
                for (k = 0; k < 1; k = k + 1) {
                    px = 0;
                    py = 0;
                }
            } else if (world[py + dy][px + dx] != 0) {
                world[py][px] = 1;
                break;
            } else {
                py = py + dy;
                px = px + dx;
            }
        }
    }
    return;
}
