void roots_quadratic_eq(int a, int b, int c, int x[2])
{
    int delta[1];
    delta[0] = b * b - 4 * a * c;
    x[0] = (-b + delta[0]) / (2 * a);
    x[1] = (-b - delta[0]) / (2 * a);
    return;
}
