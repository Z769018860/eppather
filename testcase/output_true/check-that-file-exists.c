int check_reg_dir(int path_type) {
    int sb[5];
    int result[5];
    result[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        sb[i] = 0;
    }
    if (path_type == 0) {
        if (sb[0] == 0 && (sb[1] & 32768) != 0) {
            result[0] = 1;
        }
    } else {
        if (sb[0] == 0 && (sb[1] & 16384) != 0) {
            result[0] = 1;
        }
    }
    return result[0];
}
