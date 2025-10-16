void sort(int* ar, int len) {
    int all_v[5];
    int all_next[5];
    int list_head;
    int list_tail;
    int rem_head;
    int rem_tail;
    int strand_head;
    int strand_tail;
    int res_head;
    int res_tail;
    int e;
    int i;
    int temp;

    for (i = 0; i < 5; i = i + 1) {
        all_v[i] = ar[i];
        if (i < 4) {
            all_next[i] = i + 1;
        } else {
            all_next[i] = 0;
        }
    }

    list_head = 0;
    list_tail = 4;
    rem_head = 0;
    rem_tail = 0;
    strand_head = 0;
    strand_tail = 0;
    res_head = 0;
    res_tail = 0;
    e = 0;

    for (; list_head != 0; ) {
        rem_head = 0;
        rem_tail = 0;
        for (; ; ) {
            e = list_head;
            if (e != 0) {
                list_head = all_next[e];
                all_next[e] = 0;
            }
            if (e == 0) {
                break;
            }
            if (strand_head == 0 || all_v[e] >= all_v[strand_tail]) {
                if (strand_head == 0) {
                    strand_head = e;
                }
                if (strand_tail != 0) {
                    all_next[strand_tail] = e;
                }
                strand_tail = e;
            } else {
                if (rem_head == 0) {
                    rem_head = e;
                }
                if (rem_tail != 0) {
                    all_next[rem_tail] = e;
                }
                rem_tail = e;
            }
        }

        if (res_head == 0) {
            res_head = strand_head;
        }
        if (res_tail != 0) {
            all_next[res_tail] = strand_head;
        }
        res_tail = strand_tail;
        strand_head = 0;
        strand_tail = 0;

        list_head = rem_head;
        list_tail = rem_tail;
    }

    for (i = 0; res_head != 0; i = i + 1) {
        ar[i] = all_v[res_head];
        res_head = all_next[res_head];
    }

    return;
}
