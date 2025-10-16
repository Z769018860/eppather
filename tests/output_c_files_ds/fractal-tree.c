void draw_tree(int surface_pixels[800][800], int surface_w, int surface_h, int surface_pitch, int offsetx, int offsety, int directionx, int directiony, int size, int rotation, int depth) {
    int newx;
    int newy;
    int i;
    int j;
    int color;
    
    newx = offsetx + directionx * size;
    newy = offsety + directiony * size;
    
    for (i = 0; i < surface_h; i = i + 1) {
        for (j = 0; j < surface_w; j = j + 1) {
            if ((i >= offsetx && i <= newx && j >= offsety && j <= newy) || (i >= newx && i <= offsetx && j >= newy && j <= offsety)) {
                color = 0;
                surface_pixels[i][j] = color;
            }
        }
    }
    
    if (depth > 0) {
        int left_directionx;
        int left_directiony;
        int right_directionx;
        int right_directiony;
        int new_size;
        int new_rotation;
        
        left_directionx = directionx * 921 + directiony * 383;
        left_directiony = directionx * -383 + directiony * 921;
        new_size = size * 204 / 1000 + size * 800 / 1000;
        new_rotation = rotation * 75 / 100;
        draw_tree(surface_pixels, surface_w, surface_h, surface_pitch, newx, newy, left_directionx, left_directiony, new_size, new_rotation, depth - 1);
        
        right_directionx = directionx * 921 + directiony * -383;
        right_directiony = directionx * 383 + directiony * 921;
        new_size = size * 204 / 1000 + size * 800 / 1000;
        new_rotation = rotation * 75 / 100;
        draw_tree(surface_pixels, surface_w, surface_h, surface_pitch, newx, newy, right_directionx, right_directiony, new_size, new_rotation, depth - 1);
    }
    return;
}
