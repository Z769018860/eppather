int solve_poly() {
    double p[4] = {0.0, 2.0, -3.0, 1.0};
    double z[6];
    int i;
    int j;
    double a;
    double b;
    double c;
    
    a = p[3];
    b = p[2];
    c = p[1];
    
    for (i = 0; i < 6; i = i + 1) {
        z[i] = 0.0;
    }
    
    if (a != 0.0) {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0.0) {
            z[0] = (-b + discriminant) / (2 * a);
            z[2] = (-b - discriminant) / (2 * a);
        } else if (discriminant == 0.0) {
            z[0] = -b / (2 * a);
            z[2] = z[0];
        } else {
            z[0] = -b / (2 * a);
            z[1] = (-discriminant) / (2 * a);
            z[2] = z[0];
            z[3] = -z[1];
        }
    } else if (b != 0.0) {
        z[0] = -c / b;
    }
    
    return;
}
