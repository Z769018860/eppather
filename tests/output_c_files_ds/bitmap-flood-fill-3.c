void floodfill(int img[][3], int px, int py, int bankscolor[3], int rcolor[3]) {
    int stack[1000][2];
    int top = 0;
    int width = 100;
    int height = 100;
    int x;
    int y;
    int current_color[3];
    
    stack[top][0] = px;
    stack[top][1] = py;
    top = top + 1;
    
    while (top > 0) {
        top = top - 1;
        x = stack[top][0];
        y = stack[top][1];
        
        current_color[0] = img[y][0];
        current_color[1] = img[y][1];
        current_color[2] = img[y][2];
        
        if (current_color[0] == bankscolor[0] && current_color[1] == bankscolor[1] && current_color[2] == bankscolor[2]) {
            img[y][0] = rcolor[0];
            img[y][1] = rcolor[1];
            img[y][2] = rcolor[2];
            
            if (x > 0) {
                stack[top][0] = x - 1;
                stack[top][1] = y;
                top = top + 1;
            }
            if (x < width - 1) {
                stack[top][0] = x + 1;
                stack[top][1] = y;
                top = top + 1;
            }
            if (y > 0) {
                stack[top][0] = x;
                stack[top][1] = y - 1;
                top = top + 1;
            }
            if (y < height - 1) {
                stack[top][0] = x;
                stack[top][1] = y + 1;
                top = top + 1;
            }
        }
    }
    return;
}
