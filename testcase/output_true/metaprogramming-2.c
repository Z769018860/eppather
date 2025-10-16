int function(int list_head_value, int list_next_value) {
    int n_value[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        n_value[0] = list_head_value;
        if (n_value[0]) {
            n_value[0] = list_next_value;
        }
    }
    return;
}
