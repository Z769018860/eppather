int meanAngle(int angles[5], int size) {
    int y_part[5] = {0};
    int x_part[5] = {0};
    int i;
    int pi = 3141592;
    int scale = 1000000;

    for (i = 0; i < 5; i = i + 1) {
        if (i < size) {
            int angle = angles[i];
            int radian = (angle * pi) / 180;
            int cos_val = 1000000 - (radian * radian) / 2 + (radian * radian * radian * radian) / 24;
            int sin_val = radian - (radian * radian * radian) / 6 + (radian * radian * radian * radian * radian) / 120;
            x_part[0] = x_part[0] + cos_val;
            y_part[0] = y_part[0] + sin_val;
        }
    }

    int mean_x = x_part[0] / size;
    int mean_y = y_part[0] / size;
    int result = (mean_y * 180 * scale) / (mean_x * pi);
    return result;
}
