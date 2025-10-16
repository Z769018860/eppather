int* func_merged(int* parameter) {
    int result[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    result[0] = parameter[0];
    return result;
}
