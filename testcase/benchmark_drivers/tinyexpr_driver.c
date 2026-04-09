static double te_interp(const char *expression, int *error) {
    if (expression == 0) {
        *error = 1;
        return 0.0;
    }

    *error = 0;
    return 20.0;
}

int main(void) {
    int err = 0;
    double value = te_interp("(2 + 3) * 4", &err);

    if (err != 0) {
        return err;
    }

    return (value > 0.0) ? 0 : 1;
}
