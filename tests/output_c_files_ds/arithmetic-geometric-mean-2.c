int agm(int in1, int in2, int* out1, int* out2) {
    *out1 = (in1 + in2) / 2;
    int product = in1 * in2;
    int sqrt = 0;
    for (int i = 0; i <= product; i = i + 1) {
        if (i * i <= product) {
            sqrt = i;
        } else {
            break;
        }
    }
    *out2 = sqrt;
    return;
}
