void cocktailsort(int *a, int n) {
    int flag;
    int start[2];
    int end[2];
    int inc[2];
    int it;
    int i;
    int temp;

    start[0] = 1;
    start[1] = n - 1;
    end[0] = n;
    end[1] = 0;
    inc[0] = 1;
    inc[1] = -1;

    while (1) {
        for (it = 0; it < 2; it = it + 1) {
            flag = 1;
            for (i = start[it]; i != end[it]; i = i + inc[it]) {
                if (a[i - 1] > a[i]) {
                    temp = a[i - 1];
                    a[i - 1] = a[i];
                    a[i] = temp;
                    flag = 0;
                }
            }
            if (flag) {
                return;
            }
        }
    }
    return;
}
