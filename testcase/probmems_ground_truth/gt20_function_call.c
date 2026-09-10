int probmems_helper(int *p, int index) {
    return p[index];
}

int probmems_function_call(int a[3], int x) {
    int result = 0;
    if (x > 0) {
        result = probmems_helper(a, 0);
    } else {
        result = probmems_helper(a, 2);
    }
    return result;
}
