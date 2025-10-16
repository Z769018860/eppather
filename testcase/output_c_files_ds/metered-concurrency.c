void work(int id) {
    int count = 3;
    int i;
    for (i = 0; i < 10; i = i + 1) {
        if (count > 0) {
            count = count - 1;
        }
        if (count < 3) {
            count = count + 1;
        }
    }
    return;
}
