void generate_numbers(int arr[10]) {
    int sum;
    int i;
    sum = 0;
    for (i = 0; i < 5; i = i + 1) {
        arr[i] = 1000;
        sum = sum + arr[i];
    }
    arr[3] = 1798;
    sum = sum + 798;
    for (i = 5; i < 8; i = i + 1) {
        arr[i] = 1000;
        sum = sum + arr[i];
    }
    arr[8] = 202;
    sum = sum - 798;
    arr[9] = 1000;
    sum = sum + arr[9];
    return;
}
