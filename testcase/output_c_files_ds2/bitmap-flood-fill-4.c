int floodfill(int img_width, int img_height, int img_pixels[5][5][3], int px, int py, int bankscolor_red, int bankscolor_green, int bankscolor_blue, int rcolor_red, int rcolor_green, int rcolor_blue) {
    int pixelcount[5];
    pixelcount[0] = 0;
    int tolerance[5];
    tolerance[0] = 5;
    int queue[5][2];
    int queue_size[5];
    queue_size[0] = 0;
    int thisnode[3];
    int tx;
    int ty;
    int i;
    int j;

    if ((px < 0) || (py < 0) || (px >= img_width) || (py >= img_height)) {
        return pixelcount[0];
    }

    thisnode[0] = img_pixels[px][py][0];
    thisnode[1] = img_pixels[px][py][1];
    thisnode[2] = img_pixels[px][py][2];

    if (((thisnode[0] - bankscolor_red) * (thisnode[0] - bankscolor_red) + 
         (thisnode[1] - bankscolor_green) * (thisnode[1] - bankscolor_green) + 
         (thisnode[2] - bankscolor_blue) * (thisnode[2] - bankscolor_blue)) <= (tolerance[0] * tolerance[0] * 3 * 65536)) {
        return pixelcount[0];
    }

    queue[0][0] = px;
    queue[0][1] = py;
    queue_size[0] = queue_size[0] + 1;

    for (i = 0; i < 5; i = i + 1) {
        if (queue_size[0] == 0) {
            break;
        }

        tx = queue[0][0];
        ty = queue[0][1];

        thisnode[0] = img_pixels[tx][ty][0];
        thisnode[1] = img_pixels[tx][ty][1];
        thisnode[2] = img_pixels[tx][ty][2];

        if (((thisnode[0] - bankscolor_red) * (thisnode[0] - bankscolor_red) + 
             (thisnode[1] - bankscolor_green) * (thisnode[1] - bankscolor_green) + 
             (thisnode[2] - bankscolor_blue) * (thisnode[2] - bankscolor_blue)) > (tolerance[0] * tolerance[0] * 3 * 65536)) {
            img_pixels[tx][ty][0] = rcolor_red;
            img_pixels[tx][ty][1] = rcolor_green;
            img_pixels[tx][ty][2] = rcolor_blue;
            pixelcount[0] = pixelcount[0] + 1;
        }

        for (j = 0; j < queue_size[0] - 1; j = j + 1) {
            queue[j][0] = queue[j + 1][0];
            queue[j][1] = queue[j + 1][1];
        }
        queue_size[0] = queue_size[0] - 1;

        for (j = 0; j < 4; j = j + 1) {
            int nx;
            int ny;
            if (j == 0) {
                nx = tx - 1;
                ny = ty;
            } else if (j == 1) {
                nx = tx + 1;
                ny = ty;
            } else if (j == 2) {
                nx = tx;
                ny = ty - 1;
            } else {
                nx = tx;
                ny = ty + 1;
            }

            if ((nx >= 0) && (ny >= 0) && (nx < img_width) && (ny < img_height)) {
                thisnode[0] = img_pixels[nx][ny][0];
                thisnode[1] = img_pixels[nx][ny][1];
                thisnode[2] = img_pixels[nx][ny][2];

                if (((thisnode[0] - bankscolor_red) * (thisnode[0] - bankscolor_red) + 
                     (thisnode[1] - bankscolor_green) * (thisnode[1] - bankscolor_green) + 
                     (thisnode[2] - bankscolor_blue) * (thisnode[2] - bankscolor_blue)) > (tolerance[0] * tolerance[0] * 3 * 65536)) {
                    if (((thisnode[0] - rcolor_red) * (thisnode[0] - rcolor_red) + 
                         (thisnode[1] - rcolor_green) * (thisnode[1] - rcolor_green) + 
                         (thisnode[2] - rcolor_blue) * (thisnode[2] - rcolor_blue)) > 0) {
                        img_pixels[nx][ny][0] = rcolor_red;
                        img_pixels[nx][ny][1] = rcolor_green;
                        img_pixels[nx][ny][2] = rcolor_blue;
                        queue[queue_size[0]][0] = nx;
                        queue[queue_size[0]][1] = ny;
                        queue_size[0] = queue_size[0] + 1;
                        pixelcount[0] = pixelcount[0] + 1;
                    }
                }
            }
        }
    }
    return pixelcount[0];
}
