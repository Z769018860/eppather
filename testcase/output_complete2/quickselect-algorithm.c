int qselect(int *v, int len, int k)
{
    int tmp;
    int i;
    int st;
    for (st = 0, i = 0; i < len - 1; i = i + 1) {
        if (v[i] > v[len - 1]) {
            continue;
        }
        tmp = v[i];
        v[i] = v[st];
        v[st] = tmp;
        st = st + 1;
    }
    tmp = v[len - 1];
    v[len - 1] = v[st];
    v[st] = tmp;
    if (k == st) {
        return v[st];
    } else {
        if (st > k) {
            return qselect(v, st, k);
        } else {
            return qselect(v + st, len - st, k - st);
        }
    }
    return;
}
