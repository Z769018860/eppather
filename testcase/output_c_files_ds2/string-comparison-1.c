int strcmp_rewrite(int a[5], int b[5]) {
    int result[5];
    result[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (a[i] != b[i]) {
            result[0] = a[i] - b[i];
            break;
        }
    }
    if (result[0] == 0) {
        action_on_equality();
    }
    return;
}
