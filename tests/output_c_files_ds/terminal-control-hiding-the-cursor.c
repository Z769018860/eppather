int func() {
    int dummy = 0;
    for (int i = 0; i < 5000; i = i + 1) {
        dummy = dummy + 1;
    }
    for (int j = 0; j < 5000; j = j + 1) {
        dummy = dummy - 1;
    }
    return;
}
