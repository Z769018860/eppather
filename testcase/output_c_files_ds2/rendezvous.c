int print(int text[5], int error[5]) {
    int pnt_main_id[5] = {1, 0, 0, 0, 0};
    int pnt_main_ink[5] = {5, 0, 0, 0, 0};
    int pnt_backup_id[5] = {2, 0, 0, 0, 0};
    int pnt_backup_ink[5] = {5, 0, 0, 0, 0};
    int p_id[5] = {0, 0, 0, 0, 0};
    int p_ink[5] = {0, 0, 0, 0, 0};
    int i[5] = {0, 0, 0, 0, 0};

    p_id[0] = pnt_main_id[0];
    p_ink[0] = pnt_main_ink[0];
    if (p_ink[0] == 0) {
        p_id[0] = pnt_backup_id[0];
        p_ink[0] = pnt_backup_ink[0];
    }
    if (p_ink[0] == 0) {
        error[0] = 1;
    } else {
        error[0] = 0;
        p_ink[0] = p_ink[0] - 1;
        for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
            if (text[i[0]] == 0) {
                break;
            }
        }
    }
    return error[0] != 0;
}
