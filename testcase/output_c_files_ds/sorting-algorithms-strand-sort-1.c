void sort(int* ar, int len) {
    int all_nodes[100][2];
    for (int i = 0; i < len; i = i + 1) {
        all_nodes[i][0] = ar[i];
        if (i < len - 1) {
            all_nodes[i][1] = i + 1;
        } else {
            all_nodes[i][1] = 0;
        }
    }

    int list_head = 0;
    int list_tail = len - 1;
    int rem_head = 0;
    int rem_tail = 0;
    int strand_head = 0;
    int strand_tail = 0;
    int res_head = 0;
    int res_tail = 0;

    for (int e = 0; list_head != 0 || e != 0; ) {
        rem_head = 0;
        rem_tail = 0;
        e = 0;
        while (list_head != 0) {
            e = list_head;
            list_head = all_nodes[list_head - 1][1];
            all_nodes[e - 1][1] = 0;
            if (strand_head == 0 || all_nodes[e - 1][0] >= all_nodes[strand_tail - 1][0]) {
                if (strand_head == 0) {
                    strand_head = e;
                }
                if (strand_tail != 0) {
                    all_nodes[strand_tail - 1][1] = e;
                }
                strand_tail = e;
            } else {
                if (rem_head == 0) {
                    rem_head = e;
                }
                if (rem_tail != 0) {
                    all_nodes[rem_tail - 1][1] = e;
                }
                rem_tail = e;
            }
        }

        if (res_head == 0) {
            res_head = strand_head;
        }
        if (res_tail != 0) {
            all_nodes[res_tail - 1][1] = strand_head;
        }
        res_tail = strand_tail;
        strand_head = 0;
        strand_tail = 0;
        list_head = rem_head;
        list_tail = rem_tail;
    }

    for (int i = 0; res_head != 0; i = i + 1) {
        ar[i] = all_nodes[res_head - 1][0];
        res_head = all_nodes[res_head - 1][1];
    }
    return;
}
