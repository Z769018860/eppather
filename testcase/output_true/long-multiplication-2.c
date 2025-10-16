int func(int n) {
    int arr[5];
    arr[0] = 340282366;
    arr[1] = 920938463;
    arr[2] = 463374607;
    arr[3] = 431768211;
    arr[4] = 456;
    for (int i = 0; i < 5; i = i + 1) {
        arr[i] = arr[i] + n;
    }
    return;
}
