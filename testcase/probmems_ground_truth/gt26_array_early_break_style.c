int probmems_array_early_break_style(int a[5], int key) {
    int i = 0;
    int found = -1;
    while ((i < 5) && (found < 0)) {
        if (a[i] == key) {
            found = i;
        }
        i = i + 1;
    }
    return found;
}
