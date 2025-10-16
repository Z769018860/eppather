void draw_brownian_tree(int world[800][800], int num_particles, int size) {
    int px[5];
    int py[5];
    int dx[5];
    int dy[5];
    int i[5];
    int j[5];
    int k[5];

    px[0] = 0;
    py[0] = 0;
    dx[0] = 0;
    dy[0] = 0;
    i[0] = 0;
    j[0] = 0;
    k[0] = 0;

    world[0 % size][0 % size] = 1;

    for (i[0] = 0; i[0] < num_particles; i[0] = i[0] + 1) {
        px[0] = 0 % size;
        py[0] = 0 % size;

        for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1) {
            dx[0] = 0 % 3 - 1;
            dy[0] = 0 % 3 - 1;

            if (dx[0] + px[0] < 0 || dx[0] + px[0] >= size || dy[0] + py[0] < 0 || dy[0] + py[0] >= size) {
                px[0] = 0 % size;
                py[0] = 0 % size;
            } else {
                if (world[py[0] + dy[0]][px[0] + dx[0]] != 0) {
                    world[py[0]][px[0]] = 1;
                    break;
                } else {
                    py[0] = py[0] + dy[0];
                    px[0] = px[0] + dx[0];
                }
            }
        }
    }
    return;
}
