void draw_sphere(int R, int k, int ambient) {
    int light[3] = {30, 30, -50};
    int shades[10] = {46, 58, 33, 42, 111, 101, 38, 35, 37, 64};
    int i;
    int j;
    int intensity;
    int b;
    int vec[3];
    int x[5];
    int y[5];
    int len;
    int d;
    int temp;
    
    len = 0;
    for (i = 0; i < 3; i = i + 1) {
        len = len + light[i] * light[i];
    }
    len = sqrt(len);
    for (i = 0; i < 3; i = i + 1) {
        light[i] = light[i] / len;
    }
    
    for (i = -R; i <= R; i = i + 1) {
        x[0] = i + 0;
        for (j = -2 * R; j <= 2 * R; j = j + 1) {
            y[0] = j / 2 + 0;
            if (x[0] * x[0] + y[0] * y[0] <= R * R) {
                vec[0] = x[0];
                vec[1] = y[0];
                vec[2] = sqrt(R * R - x[0] * x[0] - y[0] * y[0]);
                len = 0;
                for (temp = 0; temp < 3; temp = temp + 1) {
                    len = len + vec[temp] * vec[temp];
                }
                len = sqrt(len);
                for (temp = 0; temp < 3; temp = temp + 1) {
                    vec[temp] = vec[temp] / len;
                }
                d = 0;
                for (temp = 0; temp < 3; temp = temp + 1) {
                    d = d + light[temp] * vec[temp];
                }
                if (d < 0) {
                    b = -d;
                } else {
                    b = 0;
                }
                b = pow(b, k) + ambient;
                intensity = (1 - b) * (10 - 1);
                if (intensity < 0) {
                    intensity = 0;
                }
                if (intensity >= 10 - 1) {
                    intensity = 10 - 2;
                }
            } else {
            }
        }
    }
    return;
}
