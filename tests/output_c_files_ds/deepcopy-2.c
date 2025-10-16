void copyList(int a_data[5], int a_next[5], int a_len, int b_data[5], int b_next[5], int b_len) {
    for (int i = 0; i < a_len; i = i + 1) {
        b_data[i] = a_data[i];
        b_next[i] = a_next[i];
    }
    return;
}
