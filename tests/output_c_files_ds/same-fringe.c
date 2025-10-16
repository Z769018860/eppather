int tree_eq(int t1, int t2) {
    int stack1[100];
    int stack2[100];
    int top1 = 0;
    int top2 = 0;
    int current1 = t1;
    int current2 = t2;
    int done1 = 0;
    int done2 = 0;
    int val1 = 0;
    int val2 = 0;

    for (;;) {
        while (current1 != 0) {
            stack1[top1] = current1;
            top1 = top1 + 1;
            current1 = *((int*)(current1 + 4));
        }
        if (top1 == 0) {
            done1 = 1;
        } else {
            top1 = top1 - 1;
            current1 = stack1[top1];
            val1 = *((int*)current1);
            current1 = *((int*)(current1 + 8));
        }

        while (current2 != 0) {
            stack2[top2] = current2;
            top2 = top2 + 1;
            current2 = *((int*)(current2 + 4));
        }
        if (top2 == 0) {
            done2 = 1;
        } else {
            top2 = top2 - 1;
            current2 = stack2[top2];
            val2 = *((int*)current2);
            current2 = *((int*)(current2 + 8));
        }

        if (done1 != 0 && done2 != 0) {
            return 1;
        }
        if (done1 != 0 || done2 != 0) {
            return 0;
        }
        if (val1 != val2) {
            return 0;
        }
    }
    return 0;
}
