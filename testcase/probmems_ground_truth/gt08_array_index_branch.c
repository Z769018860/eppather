int probmems_array_index_branch(int a[3], int index) {
    int result = 0;
    if ((index >= 0) && (index < 3)) {
        result = a[index];
    } else {
        result = a[0];
    }
    return result;
}
