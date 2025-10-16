void floodfill(int img_width, int img_height, int img_pixels[1000][3], int px, int py, int bankscolor_red, int bankscolor_green, int bankscolor_blue, int rcolor_red, int rcolor_green, int rcolor_blue, int* pixelcount) {
    int queue[10000][2];
    int queue_start = 0;
    int queue_end = 0;
    int thisnode_red;
    int thisnode_green;
    int thisnode_blue;
    int tolerance_scaled = 5;
    int tx;
    int ty;
    int x;
    int y;
    int dx;
    int dy;
    int i;
    int j;
    int dist_red;
    int dist_green;
    int dist_blue;
    int dist_sq;
    int color_dist;
    int this_dist_sq;
    int this_color_dist;

    if ((px < 0) || (py < 0) || (px >= img_width) || (py >= img_height)) {
        *pixelcount = 0;
        return;
    }

    thisnode_red = img_pixels[py * img_width + px][0];
    thisnode_green = img_pixels[py * img_width + px][1];
    thisnode_blue = img_pixels[py * img_width + px][2];

    dist_red = thisnode_red - bankscolor_red;
    dist_green = thisnode_green - bankscolor_green;
    dist_blue = thisnode_blue - bankscolor_blue;
    dist_sq = dist_red * dist_red + dist_green * dist_green + dist_blue * dist_blue;
    color_dist = dist_sq / 196608;

    if (color_dist <= tolerance_scaled) {
        *pixelcount = 0;
        return;
    }

    queue[queue_end][0] = px;
    queue[queue_end][1] = py;
    queue_end = queue_end + 1;

    while (queue_start < queue_end) {
        tx = queue[queue_start][0];
        ty = queue[queue_start][1];
        queue_start = queue_start + 1;

        thisnode_red = img_pixels[ty * img_width + tx][0];
        thisnode_green = img_pixels[ty * img_width + tx][1];
        thisnode_blue = img_pixels[ty * img_width + tx][2];

        dist_red = thisnode_red - bankscolor_red;
        dist_green = thisnode_green - bankscolor_green;
        dist_blue = thisnode_blue - bankscolor_blue;
        dist_sq = dist_red * dist_red + dist_green * dist_green + dist_blue * dist_blue;
        color_dist = dist_sq / 196608;

        if (color_dist > tolerance_scaled) {
            img_pixels[ty * img_width + tx][0] = rcolor_red;
            img_pixels[ty * img_width + tx][1] = rcolor_green;
            img_pixels[ty * img_width + tx][2] = rcolor_blue;
            *pixelcount = *pixelcount + 1;
        }

        for (i = 0; i < 4; i = i + 1) {
            if (i == 0) {
                dx = -1;
                dy = 0;
            } else if (i == 1) {
                dx = 1;
                dy = 0;
            } else if (i == 2) {
                dx = 0;
                dy = -1;
            } else {
                dx = 0;
                dy = 1;
            }

            x = tx + dx;
            y = ty + dy;

            if ((x >= 0) && (y >= 0) && (x < img_width) && (y < img_height)) {
                thisnode_red = img_pixels[y * img_width + x][0];
                thisnode_green = img_pixels[y * img_width + x][1];
                thisnode_blue = img_pixels[y * img_width + x][2];

                dist_red = thisnode_red - bankscolor_red;
                dist_green = thisnode_green - bankscolor_green;
                dist_blue = thisnode_blue - bankscolor_blue;
                dist_sq = dist_red * dist_red + dist_green * dist_green + dist_blue * dist_blue;
                color_dist = dist_sq / 196608;

                if (color_dist > tolerance_scaled) {
                    this_dist_sq = (thisnode_red - rcolor_red) * (thisnode_red - rcolor_red) + 
                                  (thisnode_green - rcolor_green) * (thisnode_green - rcolor_green) + 
                                  (thisnode_blue - rcolor_blue) * (thisnode_blue - rcolor_blue);
                    this_color_dist = this_dist_sq / 196608;

                    if (this_color_dist > 0) {
                        img_pixels[y * img_width + x][0] = rcolor_red;
                        img_pixels[y * img_width + x][1] = rcolor_green;
                        img_pixels[y * img_width + x][2] = rcolor_blue;
                        *pixelcount = *pixelcount + 1;
                        queue[queue_end][0] = x;
                        queue[queue_end][1] = y;
                        queue_end = queue_end + 1;
                    }
                }
            }
        }
    }
    return;
}
