void map(int* array, int len, void(*callback)(int,int)) {
    for (int i = 0; i < len; i = i + 1) {
        callback(array[i], i);
    }
    return;
}
