void shuffle_list_do_flip_check_array(int* list, int len) {
    int n = 100;
    int a = 0;
    int b = 0;
    int buf = 0;
    int swap = 0;
    int i = 0;
    int j = 0;
    int temp = 0;
    int check = 1;

    for (i = 0; i < n; i = i + 1) {
        a = (i * 37 + 123) % len;
        b = (i * 51 + 456) % len;
        buf = list[a];
        list[a] = list[b];
        list[b] = buf;
    }

    for (j = 1; j < len; j = j + 1) {
        if (list[j] != (list[j - 1] + 1)) {
            check = 0;
            break;
        }
    }

    if (check != 0) {
        for (i = 0; i < n; i = i + 1) {
            a = (i * 73 + 789) % len;
            b = (i * 91 + 321) % len;
            buf = list[a];
            list[a] = list[b];
            list[b] = buf;
        }
    }

    for (i = 0; i < len / 2; i = i + 1) {
        temp = len - i - 1;
        swap = list[i];
        list[i] = list[temp];
        list[temp] = swap;
    }

    return;
}
