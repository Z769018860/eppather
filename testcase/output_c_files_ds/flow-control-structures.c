int func() {
    int i;
    int j;
    int flag;
    for (j = 1; j < 1000; j = j + 1) {
        flag = 0;
        for (i = 0; i < j; i = i + 1) {
            if (flag == 1) {
                break;
            }
            if (1) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    return;
}
