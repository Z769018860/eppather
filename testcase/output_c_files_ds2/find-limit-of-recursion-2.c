int get_diff(int base_addr, int x_addr) {
    int diff[5];
    diff[0] = base_addr - x_addr;
    if (diff[0] < 200) {
        int temp[5];
        temp[0] = 0;
    }
    return;
}

int recur(int base_addr) {
    int x_addr[5];
    x_addr[0] = 0;
    get_diff(base_addr, x_addr[0]);
    for (int i = 0; i < 5; i = i + 1) {
        recur(base_addr);
    }
    return;
}
