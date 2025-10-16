void draw_sphere(int R, int k, int ambient)
{
    int i;
    int j;
    int intensity;
    int b;
    int vec[3];
    int x;
    int y;
    int light[3] = {30, 30, -50};
    int len = 0;
    int d = 0;
    int temp = 0;
    int shades[10] = {46, 58, 33, 42, 111, 101, 38, 35, 37, 64};

    len = light[0] * light[0] + light[1] * light[1] + light[2] * light[2];
    len = sqrt(len);
    light[0] = light[0] / len;
    light[1] = light[1] / len;
    light[2] = light[2] / len;

    for (i = -R; i <= R; i = i + 1)
    {
        x = i;
        for (j = -2 * R; j <= 2 * R; j = j + 1)
        {
            y = j / 2;
            if (x * x + y * y <= R * R)
            {
                vec[0] = x;
                vec[1] = y;
                vec[2] = sqrt(R * R - x * x - y * y);
                len = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
                len = sqrt(len);
                vec[0] = vec[0] / len;
                vec[1] = vec[1] / len;
                vec[2] = vec[2] / len;
                d = vec[0] * light[0] + vec[1] * light[1] + vec[2] * light[2];
                if (d < 0)
                {
                    d = -d;
                }
                else
                {
                    d = 0;
                }
                temp = d;
                for (int p = 1; p < k; p = p + 1)
                {
                    temp = temp * d;
                }
                b = temp + ambient;
                intensity = (1 - b) * (10 - 1);
                if (intensity < 0)
                {
                    intensity = 0;
                }
                if (intensity >= 10 - 1)
                {
                    intensity = 10 - 2;
                }
            }
            else
            {
            }
        }
    }
    return;
}
