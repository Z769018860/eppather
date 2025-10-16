
int f(int flag, int x) {
    if (flag > 42) {
        return x + 42;
    } else if (flag == 42) {
        x = x + 1;
    } else {
        int ret = 0;

        for (int i = 0; i < x; i = i + 1) {
            ret = ret + i * x;
        }

        return ret;
    }

    return 42 + flag;
}
