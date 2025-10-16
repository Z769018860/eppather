void partial_rewritten(int* arr, int len, int func_type) {
    int i;
    if (func_type == 0) {
        for (i = 0; i < len; i = i + 1) {
            arr[i] = arr[i] * arr[i];
        }
    }
    else {
        for (i = 0; i < len; i = i + 1) {
            arr[i] = arr[i] + arr[i];
        }
    }
    return;
}
