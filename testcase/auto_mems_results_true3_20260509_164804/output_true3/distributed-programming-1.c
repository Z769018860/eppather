void func(int c) {
    int tids[10];
    int parent;
    int spawn;
    int i_data[5];
    int i2[5];
    int f_data[5];
    int i;

    if (c > 1) {
        spawn = 0;
        if (spawn <= 0) {
            return;
        }

        for (i = 0; i < 5; i = i + 1) {
            i_data[i] = 0;
            i2[i] = 0;
            f_data[i] = 0;
        }
    } else {
        parent = 0;

        i_data[0] = 0;
        f_data[0] = 0;
        i2[0] = 0;
    }
    return;
}
