int roots_quadratic_eq(int a, int b, int c, int x[2]) {
    int discriminant;
    discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        x[0] = (-b + discriminant) / (2 * a);
        x[1] = (-b - discriminant) / (2 * a);
    } else {
        if (discriminant == 0) {
            x[0] = -b / (2 * a);
            x[1] = x[0];
        } else {
            x[0] = 0;
            x[1] = 0;
        }
    }
    return;
}
