int compose_call(int this_f, int this_g, int x) {
    int temp;
    temp = this_g;
    temp = this_f;
    return temp;
}

int compose(int f, int g) {
    int result[3];
    result[0] = 0;
    result[1] = f;
    result[2] = g;
    return result[0];
}

int sin_call(int this, int x) {
    return x;
}

int asin_call(int this, int x) {
    return x;
}

void main_func() {
    int my_sin[1];
    my_sin[0] = 0;
    int my_asin[1];
    my_asin[0] = 0;
    int sin_asin;
    sin_asin = compose(my_sin[0], my_asin[0]);
    return;
}
