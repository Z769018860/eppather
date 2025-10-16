void transfer_value(int from, int to, int howmuch, int buckets[15], int bucket_mutex[15]) {
    int swapped = 0;
    int temp1;

    if ((from == to) || (howmuch < 0) || (from < 0) || (to < 0) || (from >= 15) || (to >= 15)) {
        return;
    }

    if (from > to) {
        temp1 = from;
        from = to;
        to = temp1;
        swapped = 1;
        howmuch = -howmuch;
    }

    if (howmuch > buckets[from] && !swapped) {
        howmuch = buckets[from];
    }
    if (-howmuch > buckets[to] && swapped) {
        howmuch = -buckets[to];
    }

    buckets[from] = buckets[from] - howmuch;
    buckets[to] = buckets[to] + howmuch;

    return;
}
