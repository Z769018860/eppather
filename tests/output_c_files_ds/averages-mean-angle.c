int meanAngle(int angles[5], int size) {
    int y_part = 0;
    int x_part = 0;
    int i;
    int angle;
    int pi_approx = 31416;
    int scale = 10000;
    int cos_val;
    int sin_val;
    int atan2_val;
    int result;

    for (i = 0; i < size; i = i + 1) {
        angle = angles[i];
        cos_val = angle * pi_approx / 180;
        sin_val = angle * pi_approx / 180;
        x_part = x_part + cos_val;
        y_part = y_part + sin_val;
    }

    x_part = x_part / size;
    y_part = y_part / size;
    atan2_val = y_part * scale / x_part;
    result = atan2_val * 180 / pi_approx;
    return result;
}
