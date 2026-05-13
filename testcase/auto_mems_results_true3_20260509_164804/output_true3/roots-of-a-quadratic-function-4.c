void roots_quadratic_eq(int a, int b, int c, int x[2]) {
    int discriminant[5];
    discriminant[0] = b * b - 4 * a * c;
    if (discriminant[0] > 0) {
        x[0] = (-b + discriminant[0]) / (2 * a);
        x[1] = (-b - discriminant[0]) / (2 * a);
    } else {
        x[0] = 0;
        x[1] = 0;
    }
    return;
}

void roots_quadratic_eq2(int a, int b, int c, int x[2]) {
    int q[5];
    q[0] = -0.5 * (b + (b > 0 ? 1 : -1) * (b * b - 4 * a * c));
    x[0] = q[0] / a;
    x[1] = c / q[0];
    return;
}
