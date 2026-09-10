int probmems_array_first_match(int a[3], int key) {
    int i = 0;
    while (i < 3) {
        if (a[i] == key) {
            return i;
        }
        i = i + 1;
    }
    return -1;
}
